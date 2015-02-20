import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by gaoyuan on 15-2-20.
 */
public class ErrorLog {
    public synchronized  static void writeToFile(String str) {
        Date d = new Date();
        System.out.println(d);
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");

        String dateNowStr = sdf.format(d);

        File file = new File("error" + dateNowStr + ".log");

        BufferedWriter pw = null;
        try {
            pw = new BufferedWriter(new FileWriter(file.getAbsolutePath(), true));
            pw.write(str);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                pw.flush();
                pw.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
