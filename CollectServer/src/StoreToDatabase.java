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


    public static Connection getConnection() {
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

    public static String find(String info, String table) throws SQLException {
        String resultInfo = "";

        String sql = "select ";
        sql += info;
        sql += " from ";
        sql += table;
        sql += " order by CurrentTime desc limit 0, 5";

        connection = getConnection();
        Statement dbStatue = connection.createStatement();

    //    dbStatue.execute(sql);

        ResultSet resultSet = dbStatue.executeQuery(sql);

        while (resultSet.next()){
            resultInfo += resultSet.getString(info);
        }

        connection.close();
        return resultInfo;

    }

    public static void insert(String data) throws Exception {

        String sql = "INSERT INTO MonitorInformation (clientID,MemInfo, CpuRate," +
                "NetWorkInfo,IOInfo) VALUES ";


        connection = getConnection();
        Statement dbStatue = connection.createStatement();

        sql += data;

   //     System.out.println(sql);


        dbStatue.execute(sql);
        connection.close();
    }

    public static void update(int id, String data) throws SQLException {
        String sql = "delete from clientList where ID = ";
        sql += id;
        connection = getConnection();
        Statement dbStatue = connection.createStatement();
        System.out.println(sql);
        dbStatue.execute(sql);
        sql = "insert into clientList values";
        sql += data;
        System.out.println(sql);


        dbStatue.execute(sql);
        connection.close();

        //  String sql = "UPDATE clientList SET `Name`='yuan', `CpuInfo`='is' WHERE `ID`='1'";

    }
}
