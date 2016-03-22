package com.wizehack.logExpr;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class UDPClient {
	private static UDPClient inst = null;
	
	private DatagramSocket clientSocket = null;
	private InetAddress IPAddress = null;
	private int port = 0;
	
	private UDPClient() {
		try {
			this.clientSocket = new DatagramSocket();
		} catch (SocketException e) {
			e.printStackTrace();
		}
	}
	
	public static UDPClient getInstance() {
		
		if(inst == null) {
			inst = new UDPClient();
		}
		
		return inst;
	}
	
	public boolean setup(String ipaddress, int port) {
		boolean ret = true;
		try {
			this.IPAddress = InetAddress.getByName(ipaddress);
			this.port = port;
		} catch (UnknownHostException e) {
			e.printStackTrace();
			ret = false;
		}
		return ret;
	}
	
	public void sendLog(String log)
	{
		byte[] sendData = new byte[1024];
		DatagramPacket sendPacket = null;
		
		if(log != null)
		{
			sendData = log.getBytes();
			sendPacket = new DatagramPacket(sendData, sendData.length, this.IPAddress, this.port);
			try {
				clientSocket.send(sendPacket);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public void close()
	{
		clientSocket.close();
	}

	public static void main(String[] args) {
		UDPClient udpClient;
		udpClient = UDPClient.getInstance();
		udpClient.setup("127.0.0.1", 1234);
		String log;
		
		for(int i=0; i<1000; i++)
		{
			log = "test" + i;
			udpClient.sendLog(log);
		}
		
		udpClient.close();
	}

}
