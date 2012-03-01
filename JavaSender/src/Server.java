package SenderTest;

import java.net.*;
import java.io.*;
import java.awt.Color;
import java.net.DatagramSocket;
import java.net.UnknownHostException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.NetworkInterface;

import javax.swing.SwingUtilities;
import javax.swing.JOptionPane;
import javax.swing.JFileChooser;
import java.util.UUID;
import java.util.Enumeration;

class Server extends Thread {
  /* 尝试在p处建立UDP监听,如果不成功则递增p后重新建立*/
  public Server(Node n, String name) {
    name_ = name;
    this_node_ = n;
    createSocket(Constants.BEGIN_TEST_PORT);
  }
  private static InetAddress getLocalIP()
    throws UnknownHostException, SocketException 
  {
    Enumeration<NetworkInterface> netInterfaces
      = NetworkInterface.getNetworkInterfaces();    
    InetAddress ip = null;    
    while(netInterfaces.hasMoreElements())    
    {    
      NetworkInterface ni= netInterfaces.nextElement();    
      ip = (InetAddress) ni.getInetAddresses().nextElement();    
      if( !ip.isLoopbackAddress()    
	  && ip.getHostAddress().indexOf(":") == -1)    
	break;    
    } 
    System.out.println("Local:" + ip);
    return ip;
  }
  private void createSocket(int p) {
    try {
      socket_ = new DatagramSocket(p);
      Logger.append("Bind port " + p + " successfuly!\n", Color.blue);
      this_node_.setMySelf(
	  new Peer(UUID.randomUUID(), name_, getLocalIP(), p));
    } catch (SocketException e) {
      if (p > Constants.BEGIN_TEST_PORT + 2000) {
	assert false;
      }
      //Logger.append("port " + p + " has already used!\n", Color.red);
      //Logger.append("try to port " + (p+1) + "\n", Color.red);
      createSocket(p+1);
    } catch (UnknownHostException e) {
      Logger.append("Can't find local address!\n", Color.red);
      assert false;
    }
  }

  public void run() {
    this_node_.client_ = new Client(this_node_);
    byte[] buf = new byte[1024]; //保存临时事件的缓冲区
    while(true) {
      try {
	//构建UDP Packet用来存放待接受的事件
	DatagramPacket p = new DatagramPacket(buf, buf.length); 
	socket_.receive(p); // 阻塞接受

	//尝试将接受到的数据转换成对应事件
	ObjectInputStream ois = new ObjectInputStream(
	    new ByteArrayInputStream(p.getData()));
	Object o =  ois.readObject();


	String o_name = o.getClass().getName();
	if (o.getClass() == EventLogin.class) {
	  this_node_.addNode(((EventLogin)o).getPeer());
	} else if (o.getClass() == EventLogout.class) {
	  this_node_.delNode(((EventLogout)o).getUUID());
	} else if (o.getClass() == EventMessage.class) {
	  EventMessage e = (EventMessage)o;
	  this_node_.receiveMessage(e.getUUID(), e.getMessage());
	} else if (o.getClass() == EventTransferRequest.class) {
	  EventTransferRequest e = (EventTransferRequest)o;
	  doTransferRequest(e);
	} else if (o.getClass() == EventTransferResponse.class) {
	  EventTransferResponse e = (EventTransferResponse)o;
	  doTransferResponse(e);
	} else {
	  Logger.append("Receive an unknow Package\n", Color.red);
	}
      } catch (ClassNotFoundException e) {
	//忽略无效数据
	System.out.println("Not an validate object!");
      } catch (IOException e) {
	System.out.println("Server run() 1 error!");
	assert false;
      }
    }
  }

  private void doTransferResponse(EventTransferResponse e) {
    if (e.accept) {
      //同意接受, 获取远方监听端口.
      
      //告诉发送代理 远方等待接受文件的TCP 端口 以及地址 
      this_node_.fser_.setSocket(this_node_.getAddrByUUID(e.getUUID()),
	  e.open_port);
      //开启线程发送文件
      new Thread(this_node_.fser_).run();
    } else {
      //如果远方拒绝接受
      Logger.append(this_node_.getNameByUUID(e.getUUID()) 
	  + " rejected receive files requset\n", Color.red);
    }
  }

  private void doTransferRequest(final EventTransferRequest event) {
    try {
    SwingUtilities.invokeAndWait(new Runnable() {
      public void run() {
	//确认允许接受发送者发送的文件
	String name = this_node_.getNameByUUID(event.getUUID());
	if(JOptionPane.showConfirmDialog(null,
	    "[" + name + "]" + 
	    "  want send somefile to you, may I receive?", 
	    "Accept ?",
	    JOptionPane.OK_CANCEL_OPTION) == 
	  JOptionPane.OK_OPTION) {
	  //如果允许远方节点传送文件到本机,则继续

	  JFileChooser chooser = new JFileChooser();
	  chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
	  if (JFileChooser.APPROVE_OPTION == chooser.showOpenDialog(null)) {

	    //创建文件接受者;  参数存放文件的根目录
	    this_node_.frer_ = new FileReceiver(
	      chooser.getSelectedFile().getAbsolutePath()
	      );

	    //获取本节点的表示符以完成Event的构建
	    UUID u = this_node_.getMySelf().uuid;

	    //sendEvent的后两个参数是将要发送的地址和端口
	    this_node_.client_.sendEvent(
	      new EventTransferResponse(u, this_node_.frer_.getListenPort()),
	      this_node_.getAddrByUUID(event.getUUID()),
	      this_node_.getPortByUUID(event.getUUID()));

	    Logger.append("[" + this_node_.getNameByUUID(event.getUUID()) + "] ",
		Color.BLUE);
	    Logger.append("has accepted send file request!\n", Color.RED);

	  }

	} else {
	  UUID u = this_node_.getMySelf().uuid;
	  this_node_.client_.sendEvent(
	      new EventTransferResponse(u),
	      this_node_.getAddrByUUID(u),
	      this_node_.getPortByUUID(u)
	      );
	}
      }
    });
    //另外开启线程 等待发送文件
    new Thread(this_node_.frer_).run();
    } catch (Exception e) {
      Logger.append("Unknow ERROR!" + e.getMessage() + "\n", Color.RED);
      e.printStackTrace();
    }
  }
  private DatagramSocket socket_;
  private String name_;
  private Node this_node_;
}
