package SenderTest;

import java.awt.Color;
import javax.swing.JTextPane;
import javax.swing.SwingUtilities;
import javax.swing.text.*;
import java.util.UUID;
import java.net.InetAddress;
import java.io.Serializable;

interface Constants {
	final static int BEGIN_TEST_PORT = 1024;
}

class Peer implements Serializable{
	public UUID uuid;
	public String name;
	public InetAddress addr;
	public int port;
	public boolean equals(Peer right) {
		return this.uuid.equals(right.uuid);
	}
	public String toString() {
		return name + "@" + addr.getHostAddress() + ":" + port;
	}
	public Peer(UUID u, String n, InetAddress a, int p) {
		uuid = u;
		name = n;
		addr = a;
		port = p;
	}
}

abstract class EventBase extends Object implements Serializable {
	public EventBase(UUID uuid) {
		uuid_ = uuid;
	}
	public UUID getUUID() {
		return uuid_;
	}
	protected UUID uuid_;
}

class EventLogin extends EventBase {
	public EventLogin(Peer p) {
		super(p.uuid);
		if (p == null)
			assert false;
		peer_ = p;
	}
	public Peer getPeer() {
		return peer_;
	}
	Peer peer_;
}
class EventLogout extends EventBase {
	public EventLogout(UUID uuid){
		super(uuid);
	}
}
class EventMessage extends EventBase{
	public EventMessage(UUID uuid, String msg) {
		super(uuid);
		message_ = msg;
	}
	public String getMessage() {
		return message_;
	}
	private String message_;
}
class EventTransferRequest extends EventBase {
	public EventTransferRequest(UUID u) {
		super(u);
	}
}
class EventTransferResponse extends EventBase {
	public int open_port;
	public boolean accept;
	public EventTransferResponse(UUID u, int p) {
		super(u);
		open_port = p;
		accept = true;
	}
	public EventTransferResponse(UUID u) {
		super(u);
		accept = false;
	}
}


class Logger {
	static private JTextPane text_= null;
	static public void setLogView(JTextPane c) {
		Logger.text_ = c;
	}
	public static void append(final String message, final Color c) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				StyleContext sc = StyleContext.getDefaultStyleContext();
				AttributeSet aset = sc.addAttribute(SimpleAttributeSet.EMPTY,
					StyleConstants.Foreground, c);
				int len = text_.getDocument().getLength(); 
				text_.setCaretPosition(len); 
				text_.setCharacterAttributes(aset, false);
				text_.replaceSelection(message); 
			}
		});
	}
	public static void append(final String message) {
		append(message, Color.black);
	}
}
