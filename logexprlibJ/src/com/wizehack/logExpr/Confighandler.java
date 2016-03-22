package com.wizehack.logExpr;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonReader;

public class Confighandler {

	private String confFile = null;
	private ConfData confData = null;
	
	public Confighandler(String confFile) {
		this.confFile = confFile;
		this.confData = ConfData.getInstance();
	}
	
	public String getProcessId() {
		return this.confData.getInstance().getProcessId();
	}

	public String getPriority() {
		return this.confData.getInstance().getPriority();
	}

	public String getAddress() {
		return this.confData.getInstance().getAddress();
	}

	public int getPort() {
		return this.confData.getInstance().getPort();
	}
	
	public boolean isParsed(){
		
		if(confData.getProcessId() == null){
			return false;
		} else {
			return true;
		}
	}
	
	public boolean parse(){
		boolean parsed = false;
		
		InputStream fis = null;
		JsonReader jsonReader = null;
		JsonObject jsonObject = null;
				
		try {
			fis = new FileInputStream(this.confFile);
			
			//create JsonReader object
			jsonReader = Json.createReader(fis);
			
			//get JsonObject from JsonReader
			jsonObject = jsonReader.readObject();
			
			// close IO resource and JsonReader
			jsonReader.close();
			fis.close();
			
			String processId = jsonObject.getString("processId");
			String priority = jsonObject.getString("priority");
			String address = jsonObject.getString("address");
			int port = -1;
			
			try {
				port = jsonObject.getInt("port");
			} catch (NullPointerException e) {
				e.printStackTrace();
				System.out.println("NullPointerException");
				return false;
			} catch (ClassCastException e) {
				e.printStackTrace();
				System.out.println("ClassCastException");

				return false;
			}
			
			if(processId == null) {
				parsed = false;
				System.out.println("processId");

			} else if (priority == null) {
				parsed = false;
				System.out.println("priority");

			} else if (address == null ) {
				parsed = false;
				System.out.println("address");

			} else if (port == -1 ) {
				parsed = false;
				System.out.println("port");

			} else {
				this.confData.setProcessId(processId);
				this.confData.setPriority(priority);
				this.confData.setAddress(address);
				this.confData.setPort(port);
				parsed = true;
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			parsed = false;
		} catch (IOException e) {
			e.printStackTrace();
			parsed = false;
		} 
		
		return parsed;
	}
}
