import java.io.File;
import java.io.IOException;

import com.wizehack.logExpr.Confighandler;
import com.wizehack.logExpr.Logger;


public class JavaProcess {

    private JavaProcess() {}        

    public static int exec(Class klass) throws IOException,
                                               InterruptedException {
        String javaHome = System.getProperty("java.home");
        String javaBin = javaHome +
                File.separator + "bin" +
                File.separator + "java";
        String classpath = System.getProperty("java.class.path");
        String className = klass.getCanonicalName();

        ProcessBuilder builder = new ProcessBuilder(
                javaBin, "-cp", classpath, className);

        Process process = builder.start();
        process.waitFor();
        return process.exitValue();
    }

	public static void main(String[] args) {
		try {
			JavaProcess.exec(LoggerA.class);
			JavaProcess.exec(LoggerB.class);
			JavaProcess.exec(LoggerC.class);
			JavaProcess.exec(LoggerD.class);
			JavaProcess.exec(LoggerE.class);
			JavaProcess.exec(LoggerF.class);
			JavaProcess.exec(LoggerG.class);
			JavaProcess.exec(LoggerH.class);
			JavaProcess.exec(LoggerI.class);
			JavaProcess.exec(LoggerJ.class);

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
} 
