/**
 * Created by gaoyuan on 14-11-26.
 */

import java.sql.SQLException;

/**
 * Created by gaoyuan on 14-11-25.
 */

public class DealGetRequest {
    public static String getInfo(int clientID, String order) throws SQLException {
        if (order.equals("BaseInfo")){
            return getClientBaseInfo(clientID);
        }
        else if(order.equals("CpuInfo")){
            return getCpuInfo(clientID);
        }
        else if(order.equals("MemInfo")){
            return getMemInfo(clientID);
        }
        else if (order.equals("CpuRate")){
            return getCpuRate(clientID);
        }
        else if (order.equals("NetWorkInfo")){
            return getNetWorkInfo(clientID);
        }
        else if(order.equals("DiskIO")){
            return getDiskIO(clientID);
        }
        else{
            return "No info";
        }
    }
    public static String getClientBaseInfo(int clientID) throws SQLException {
        return StoreToDatabase.find("Name", "clientList", clientID);
    }
    public static String getCpuInfo(int clientID) throws SQLException {
        return StoreToDatabase.find("CpuInfo", "clientList", clientID);
    }
    public static String getMemInfo(int clientID) throws SQLException{
        return StoreToDatabase.find("MemInfo", "MonitorInformation", clientID);
    }
    public static String getCpuRate(int clientID) throws SQLException{
        return StoreToDatabase.find("Cpurate", "MonitorInformation", clientID);
    }
    public static String getNetWorkInfo(int clientID) throws SQLException{
        return StoreToDatabase.find("NetWorkInfo", "MonitorInformation", clientID);
    }
    public static String getDiskIO(int clientID) throws SQLException{
        return StoreToDatabase.find("IOInfo", "MonitorInformation", clientID);
    }
}

