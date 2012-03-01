package SenderTest;

import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.NetworkInterface;
import java.net.UnknownHostException;
import java.util.Enumeration;
import java.util.UUID;
import java.io.*;
import javax.swing.SwingUtilities;


class Client {
  public Client(Node n) {
    this_node_ = n;
    detectLocalNodes();
  }
  private static InetAddress getBoardcast()
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
	  && ip.getHostAddress().indexOf(":") == -1)   {
	 return ni.getInterfaceAddresses().get(0).getBroadcast();
      }
    } 
    return null;
  }



  /**
   * show 使用mySelft().addr:port 向event.uuid 节点发送信息
   * @param event 需要发送的事件
   * @param addr 目标地址
   * @param port 目标端口
   */
  public void sendEvent(EventBase event, InetAddress addr, int port) {
    try {
      ByteArrayOutputStream bos = new ByteArrayOutputStream();
      ObjectOutputStream oos;
      oos = new ObjectOutputStream(bos);
      oos.writeObject(event);
      byte[] buf = bos.toByteArray();
      DatagramSocket s;
      s = new DatagramSocket();
      DatagramPacket p = new DatagramPacket(buf, buf.length, addr, port);
      s.send(p);
    } catch (SocketException e) {
      System.out.println("sendEvent error! \n");
      assert false;
    } catch (IOException e) {
      System.out.println("IO error!\n");
      assert false;
    }
  }

  /*从BEGIN_TEST_PORT处开始尝试检测本机的节点*/
  private void detectLocalNodes() {
    Logger.append("Begin Detecting Local node!\n");

    Peer peer = this_node_.getMySelf();
    for (int i=Constants.BEGIN_TEST_PORT;
	i < Constants.BEGIN_TEST_PORT+4; 
	i++)
    {
      try {
	//在端口i处通过局域网广播探测是否存在其他节点
	sendEvent(new EventLogin(peer), getBoardcast(), i);

	//广播消息并不发送一份到本机,所有添加一个发送到本机的包
	sendEvent(new EventLogin(peer), peer.addr, i);
      } catch (UnknownHostException e) {
	System.out.println("无法解析广播地址");
	assert false;
      } catch (SocketException e) {
	System.out.println("Socket error");
	assert false;
      }
    }
  }

  private Node this_node_;
}
