package com.wizehack.logExpr;
import java.io.StringWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonWriter;

public class Logger {
	private static Logger instance = null;
	private static Confighandler confighandler = null;
	private enum priority {DEBUG, INFORM, ERROR, FAILURE, CRITICAL, NOT_DEFINED};
	private static String processid = null;
	private static priority currentPriority = priority.NOT_DEFINED;
	private static UDPClient udpclient = null;
	
	public void finalize() {
		Logger.processid = null;
		Logger.currentPriority = priority.NOT_DEFINED;
		Logger.udpclient.close();
		Logger.udpclient = null;
	}
	
	private Logger(Confighandler config) {

		if(confighandler == null) {
			confighandler = config;
		}
		
		if(!confighandler.isParsed()){ //is NOT parsed
			if(confighandler.parse()) {
				Logger.udpclient = UDPClient.getInstance();
				if(Logger.udpclient.setup(confighandler.getAddress(), confighandler.getPort())) {
					Logger.currentPriority = this.getPriority(confighandler.getPriority());
					Logger.processid = confighandler.getProcessId();
				} else {
					System.out.println("udp failed");
				}

			} else {
				System.out.println("configuration failed");
			}
		} else {
			if(Logger.udpclient == null) {
				Logger.udpclient = UDPClient.getInstance();
				Logger.udpclient.setup(confighandler.getAddress(), confighandler.getPort());
			}
			
			if(Logger.currentPriority == priority.NOT_DEFINED) {
				Logger.currentPriority = this.getPriority(confighandler.getPriority());
			}
			
			if(Logger.processid == null) {
				Logger.processid = confighandler.getProcessId();
			}
		}
	}
	
	public static synchronized Logger getInstance(Confighandler config) {
		if(instance == null) {
			instance = new Logger(config);
		}
		
		return instance;
	}

	public priority getPriority(String level) {
		priority prior = priority.NOT_DEFINED;
		
		if(level.matches("debug")) {
			prior = priority.DEBUG;
		} else if (level.matches("inform")) {
			prior = priority.INFORM;
		} else if (level.matches("error")) {
			prior = priority.ERROR;
		} else if (level.matches("failure")) {
			prior = priority.FAILURE;
		} else if (level.matches("critical")) {
			prior = priority.CRITICAL;
		} else {
			prior = priority.NOT_DEFINED;
		}
		
		return prior;
	}
	
	public void deliver(String level, String log) {
		if(Logger.currentPriority.ordinal() <= this.getPriority(level).ordinal()) {
		    SimpleDateFormat sdfDate = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");
		    Date now = new Date();
		    String strDate = sdfDate.format(now);
		    		
			int line = Thread.currentThread().getStackTrace()[2].getLineNumber();
			String method = Thread.currentThread().getStackTrace()[2].getMethodName();
			String file = Thread.currentThread().getStackTrace()[2].getFileName();
			
			String insertMsg = null;
			if(log.length() > 4096) {
				insertMsg = log.substring(0, 4095);
			} else {
				insertMsg = log;
			}
			
			JsonObject jsonObject = Json.createObjectBuilder()
					.add("process_log_id", Logger.processid)
					.add("time", strDate)
					.add("log", Json.createObjectBuilder()
							.add("file", file)
							.add("func", method)
							.add("line", line)
							.add("level", level)
							.add("msg", insertMsg).build()
					).build();
			
			StringWriter stringWriter = new StringWriter();
			JsonWriter writer = Json.createWriter(stringWriter);
			writer.writeObject(jsonObject);
			writer.close();
			udpclient.sendLog(stringWriter.getBuffer().toString());
		} 
	}

}
