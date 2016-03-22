package com.wizehack.logExpr;

public class ConfData {

	private static ConfData inst = null;
	private String processId = null;
	private String priority = null;
	private String address = null;
	private int port = 0;
	
	private ConfData(){}
	public static ConfData getInstance()
	{
		if(inst == null)
		{
			inst = new ConfData();
		}
		
		return inst;
	}
	
	public String getProcessId() {
		return processId;
	}
	public void setProcessId(String processId) {
		this.processId = processId;
	}
	public String getPriority() {
		return priority;
	}
	public void setPriority(String priority) {
		this.priority = priority;
	}
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	public int getPort() {
		return port;
	}
	public void setPort(int port) {
		this.port = port;
	}
}
