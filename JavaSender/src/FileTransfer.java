package SenderTest;
import java.util.*;
import java.io.*;
import java.net.*;
import java.awt.Color;

class FileReceiver implements Runnable {
  ServerSocket socket_;
  int port_;
  String base_;
  public FileReceiver(String base) {
    base_ = base;
    try {
    socket_ = new ServerSocket();
    socket_.bind(null);
    port_ = socket_.getLocalPort();

    Logger.append("Begin listening Port " + port_ + " for receive files!\n",
	Color.GRAY);
    } catch (Exception e) {
      System.out.println("FileReceiver init error!");
      assert false;
    }
  }
  public int getListenPort() {
    return port_;
  }
  public void run() {
    try {
      Socket client_socket = socket_.accept();
      DataInputStream di = new DataInputStream(
	  new BufferedInputStream(client_socket.getInputStream()));
      boolean no_error = true;
      while (no_error) {
	try {
	  String filename = di.readUTF(); //第一次读取文件名

	  Logger.append("Begining receive file " + base_+filename + "\n",
	      Color.GRAY);

	  //首先检测文件所在目录是否存在,若不存在则创建目录
	  new File(base_+filename).getParentFile().mkdirs();

	  DataOutputStream ds =  new DataOutputStream(
	      new BufferedOutputStream(
		new FileOutputStream(base_ + filename)));

	  long filelength = di.readLong(); //第二次读取文件长度

	  while (filelength > 0 ) { //第三次读取文件内容
	    filelength--;
	    int c = di.read();
	    ds.write(c);
	  }
	  ds.flush();
	  ds.close();

	  filelength = 0;
	  Logger.append("End receive file " + base_+filename + "\n", 
	      Color.GRAY);
	} catch (IOException e) {
	  //如果出现错误, di == null 是因为所有文件都已经传输完毕 socket被peer关闭
	  no_error = false;
	}
      }
      di.close();
      client_socket.close();
      socket_.close();
      Logger.append("All files has been received!\n", Color.BLUE);
    } catch (IOException e) {
      System.out.println("FileReceiver run() 2 error!" + e.getMessage());
      assert false;
    }
  }
}

class FileSender implements Runnable {
  private String base_;
  private Socket socket_;
  DataOutputStream ds_; 

  public FileSender(String base) {
    base_ = base;
    socket_ = new Socket();
  }

  public void setSocket(InetAddress addr, int port) {
    try {
      socket_.connect(new InetSocketAddress(addr, port));
      ds_ = new DataOutputStream(
	  new BufferedOutputStream(socket_.getOutputStream())
	  );
    } catch (IOException e) {
      System.out.println("FileSender.setSocket() error! " + e.getMessage());
      assert false;
    }
  }
  private void scanFiles(File f) {
    if (f.isDirectory()) {
      for (File nextfile : f.listFiles()) {
	scanFiles(nextfile);
      }
    } else {
      String abs = f.getAbsolutePath();
      String rel = abs.substring(base_.length());
      try {
	sendFile(rel);
      } catch (IOException e) {
	Logger.append("Send file " + abs + "  ERROR!:\n\t", Color.RED);
	Logger.append(e.getMessage() + "\n", Color.RED);
      }
    }
  }
  private void sendFile(String filename) throws IOException {
    //获取待发送文件的输入流
    DataInputStream di = new DataInputStream(
	new BufferedInputStream(
	  new FileInputStream(base_ + filename)));

    Logger.append("Begin Send file " + base_+filename + "\n", Color.BLUE);
    ds_.writeUTF(filename); //第一次发送相对路径

    //第二次发送文件长度
    ds_.writeLong(new File(base_ + filename).length());

    //第三次读取文件内容并发送到socket上去
    int c = 0;
    while ((c = di.read()) != -1) {
      ds_.write(c); 
    }
    ds_.flush(); //刷新socket
    di.close(); //关闭写入的文件, 发送流不关闭,继续发送下一个文件
    Logger.append("End Send file " + base_+filename + "\n", Color.GRAY);
  }

  public void run() {
    Logger.append("Beging send file.\n", Color.BLUE);
    File root = new File(base_);
    try {
      if (root.isDirectory())
	//如果选择的是目录 则递归传递
	scanFiles(root);
      else {
	//如果选择的是普通文件 则直接传输
	//手动设置baseDIR 和 文件名
	base_ = root.getParent() + File.separator;
	sendFile(File.separator + root.getName());
      }
      ds_.close();
    } catch (IOException e) {
      Logger.append("Send file ERROR! " + e.getMessage() +"\n", Color.RED);
    }
    Logger.append("Send file completed.\n", Color.BLUE);
  }
}
