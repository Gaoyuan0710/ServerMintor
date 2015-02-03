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

    public static String find(String info, String table, int clientID) throws SQLException {
        String resultInfo = "";

        String sql = "select ";
        sql += info;
        sql += " from ";
        sql += table;

        if (!(clientID == 0)) {
            if (!table.equals("clientList")) {
                sql += " where clientID = ";


            } else {
                sql += " where ID = ";

            }
            sql += clientID;
        }
        if (!table.equals("clientList")) {
            sql += " order by CurrentTime desc limit 0, 5";
        }


        connection = getConnection();
        Statement dbStatue = connection.createStatement();

    //    dbStatue.execute(sql);

        System.out.println(sql);
        ResultSet resultSet = dbStatue.executeQuery(sql);

        resultInfo = "{\"result\":";
        boolean flag = false;
        boolean arrayFlag = false;
        boolean beginFlag = true;

        while (resultSet.next()){
            if (!resultSet.getString(info).startsWith("[") && beginFlag == true){
                resultInfo += "[[\"";
                flag = true;
                beginFlag = false;
            }
            else if (resultSet.getString(info).startsWith("[") && beginFlag == true){
                resultInfo += "[";
                arrayFlag = true;
                beginFlag = false;
            }
            resultInfo += resultSet.getString(info);

            if (!arrayFlag){
                resultInfo += "\"],[\"";
            }
            else {
                resultInfo += ",";
            }

        }

        if (flag){
            resultInfo = resultInfo.substring(0, resultInfo.length() - 4);
            resultInfo += "]]";
        }
        if (arrayFlag){

            resultInfo = resultInfo.substring(0, resultInfo.length() - 1);
            resultInfo += "]";
        }
        resultInfo += "}";

        connection.close();
        return resultInfo;

    }

    public static void insert(String data) throws Exception {

        String sql = "INSERT INTO MonitorInformation (clientID,MemInfo, CpuRate," +
                "NetWorkInfo,IOInfo,Ip) VALUES ";


        connection = getConnection();
        Statement dbStatue = connection.createStatement();

        sql += data;

        System.out.println(sql);


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
    public static String findBaseInfo(int id) throws SQLException {
        String sql = "";
        String data = "";

        if (id != 0) {
            sql = "select Name from clientList where ID = ";
            sql += id;
        }
        else {
            sql = "select Name from clientList";
        }

        connection = getConnection();
        Statement dbStatue = connection.createStatement();

        ResultSet resultSet = dbStatue.executeQuery(sql);
        while (resultSet.next()) {
            data += resultSet.getString("Name");
            data += ",";
        }
        data = data.substring(0, data.length() - 1);
        return data;
    }

}
