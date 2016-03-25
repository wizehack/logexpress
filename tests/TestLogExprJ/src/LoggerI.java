import com.wizehack.logExpr.Confighandler;
import com.wizehack.logExpr.Logger;


public class LoggerI {

	public static void main(String[] args) {
		Logger logger = Logger.getInstance(new Confighandler("./res/loggerI.json"));
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		for(int i=1; i<=1000; i++){
			String str = i + "th TEST ";
			logger.deliver("debug", str);
		}
	}

}
