import java.sql.*;

/**
 * Created by gaoyuan on 14-11-7.
 */
public class StoreToDatabase {
    private static String driver = "com.mysql.jdbc.Driver";
    private static String url = "jdbc:mysql://localhost:3306/ServerMonitor";
    private static String user = "gaoyuan";
    private static String passwd = "123456";
    private static Connection connection;




    public static Connection getConnection(){
        Connection connectionStatus = null;
        try {
            Class.forName(driver);
            connectionStatus = DriverManager.getConnection(url, user, passwd);

        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return connectionStatus;
    }
    public static void insert(int id, String data) throws Exception {
        connection = getConnection();
        String sql = "insert into test values(";
        sql += id;
        sql += ",'";
        sql += data;
        sql += "');";
System.out.println(sql);
       Statement dbStatue = connection.createStatement();

        dbStatue.execute(sql);
        connection.close();
    }


}
