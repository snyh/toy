package SenderTest;

import javax.swing.text.*;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.JTextPane;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JComboBox;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.border.EmptyBorder;
import javax.swing.SwingUtilities;
import javax.swing.JOptionPane;
import javax.swing.JFileChooser;
import javax.swing.UIManager;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.BorderLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import java.util.Hashtable;
import java.util.UUID;
import java.net.InetAddress;
import java.util.Iterator;

public class Node {
  private Peer myself_;
  private Peer select_peer_;
  protected FileSender fser_;
  protected FileReceiver frer_;

  private Hashtable<UUID, Peer> peers_;

  protected Server server_;
  protected Client client_;
  private NodeView view_;

  public InetAddress getAddrByUUID(UUID u) {
    return peers_.get(u).addr;
  }
  public int getPortByUUID(UUID u) {
    return peers_.get(u).port;
  }
  public String getNameByUUID(UUID u) {
    return peers_.get(u).name;
  }

  public Node() {
    peers_ = new Hashtable<UUID, Peer>();

    view_ = new NodeView(this);
    view_.setVisible(true);

    server_ = new Server(this, view_.name);
    new Thread(server_).start();

    /*
    无法保证client_在 Server 运行之前创建,因此将new Client放在Server.run中
    client_ = new Client(this);
    */
  }
  public void setMySelf(Peer p) {
    myself_ = p;
  }
  public Peer getMySelf() {
    return myself_;
  }
  public void addNode(Peer p) {
    //检测当前Node 是否已经存储,如果存储则不予处理
    //若不存在则添加记录,并向所有节点广播此节点

    if (peers_.get(p.uuid) == null) {
      //首先将新发现的节点存放到peers_中,然后显示到ComboBox上并提示发现新节点
      peers_.put(p.uuid, p); 
      view_.addNode(p);
      Logger.append("["+p.name + "]", Color.BLUE);
      Logger.append(" has login!\n", Color.red);

      //将新发现的节点发送给登录到本节点的Peer上去
      Iterator<Peer> peer_it = peers_.values().iterator();
      while (peer_it.hasNext()) {
	//向tmp发送所有已经登录到本节点的信息
	Peer tmp = peer_it.next();
	if (tmp == myself_) break;

	//循环发送
	Iterator<Peer> info_it = peers_.values().iterator();
	while(info_it.hasNext()) {
	  Peer p_info = info_it.next(); //节点信息
	  System.out.println(p_info);

	  client_.sendEvent(new EventLogin(p_info), tmp.addr, tmp.port);
	}
      }
    }
  }
  public void delNode(UUID u) {
    Peer p = peers_.get(u);
    if (p != null) {
      peers_.remove(u);
      view_.delNode(p);
      Logger.append("["+p.name + "]", Color.BLUE);
      Logger.append(" has logout!\n", Color.RED);
    }
  }
  public void logout() {
    Iterator<Peer> it = peers_.values().iterator();
    while (it.hasNext()) {
      //回送所有当前节点已经知道的节点信息
      Peer tmp = it.next();
      client_.sendEvent(new EventLogout(myself_.uuid), tmp.addr, tmp.port);
    }
    System.out.println("logouted! \n");
    System.exit(0);
  }
  public void receiveMessage(UUID u, String msg) {
    Logger.append("[From:" + peers_.get(u).name + "]: ", Color.BLUE);
    Logger.append(msg+"\n", Color.cyan);
  }
  public void sendMessage(UUID u, String msg) {
    if (u.equals(myself_.uuid)) { //向自己发送信息使用灰色标记
      Logger.append("[Yourself]: ", Color.BLUE);
      Logger.append(msg+"\n", Color.GRAY);
      //并且并不实际发送信息
    } else {
      Logger.append("[To:" + peers_.get(u).name + "]: ", Color.BLUE);
      Logger.append(msg+"\n");
      client_.sendEvent(new EventMessage(u, msg),
	  peers_.get(u).addr, peers_.get(u).port);
    }
  }

  public static void main(String[] args) {
    SwingUtilities.invokeLater(new Runnable() {
      public void run() {
	Node n1 = new Node();
      }
    });
  }
}


class NodeView extends JFrame {
  public String name;
  public NodeView(Node n) {
    this_node_ = n;

    try {
      UIManager.setLookAndFeel(
	  UIManager.getSystemLookAndFeelClassName());
    } catch(Exception e) {
      System.out.println("Error setting Java LAF: " + e);
    }
    initUI();



    //获取登录名
    name = JOptionPane.showInputDialog("Please input you nickname");
    setTitle(name + "@ Java Sender Test!");

    g_send_message_.addActionListener(new ActionListener() {
      public void actionPerformed(final ActionEvent e) {
	Peer p = (Peer)g_nodes_.getSelectedItem();
	this_node_.sendMessage(p.uuid, g_message_field_.getText());
      }
    });

    g_transfer_.addActionListener(new ActionListener() {
      public void actionPerformed(final ActionEvent e) {
	JFileChooser chooser = new JFileChooser();
	chooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
	if (JFileChooser.APPROVE_OPTION == chooser.showOpenDialog(null)) {
	  Peer peer = (Peer)g_nodes_.getSelectedItem();
	  String dirname = chooser.getSelectedFile().getAbsolutePath();
	  Logger.append("Ready transfer " + dirname
	    + " to" + peer.name + " \n" ,
	    Color.red);
	  this_node_.fser_ = new FileSender(dirname);
	  this_node_.client_.sendEvent(
	    new EventTransferRequest(this_node_.getMySelf().uuid),
	    this_node_.getAddrByUUID(peer.uuid),
	    this_node_.getPortByUUID(peer.uuid)
	    );
	}
      }
    });

    this.addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent e) {
	this_node_.logout();
      }
    });
  }
  public void addNode(final Peer p) {
    SwingUtilities.invokeLater(new Runnable() {
      public void run() {
	g_nodes_.addItem(p);
      }
    });
  }
  public void delNode(final Peer p) {
    SwingUtilities.invokeLater(new Runnable() {
      public void run() {
	g_nodes_.removeItem(p);
      }
    });
  }


  private final void initUI() {
    JPanel panel = new JPanel(new BorderLayout());
    panel.setBorder(new EmptyBorder(new Insets(20, 20, 20, 20)));

    JPanel topbox = new JPanel();
    topbox.setLayout(new BoxLayout(topbox, BoxLayout.X_AXIS));
    panel.add(topbox, BorderLayout.NORTH);

    g_nodes_ = new JComboBox();
    String init_str = "This message will send to peer!";
    g_message_field_ = new JTextField(init_str);
    //g_message_field_.select(0, init_str.length());
    g_send_message_ = new JButton("Send");
    topbox.add(g_nodes_);
    topbox.add(g_message_field_);
    topbox.add(g_send_message_);


    g_text_pane_ = new JTextPane();
    //g_text_pane_.setEditable(false);
    g_text_pane_.setPreferredSize(new Dimension(450, 250));
    Logger.setLogView(g_text_pane_); //设置Logger输出位置
    JScrollPane s = new JScrollPane();
    s.setViewportView(g_text_pane_);
    panel.add(s);


    JPanel bottombox = new JPanel();
    bottombox.setLayout(new BoxLayout(bottombox, BoxLayout.X_AXIS));
    panel.add(bottombox, BorderLayout.SOUTH);


    JButton b = new JButton("Clear");
    b.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
	g_text_pane_.setText("");
      }
    });
    bottombox.add(b);

    g_transfer_ = new JButton("Transfer Files");
    bottombox.add(g_transfer_);


    add(panel);
    pack();
    setLocationRelativeTo(null);
  }

  /* GUI相关的成员 */
  private JComboBox g_nodes_;
  private JTextField g_message_field_;
  private JButton g_send_message_;
  private JTextPane g_text_pane_;
  private Node this_node_;
  private JButton g_transfer_;
}
