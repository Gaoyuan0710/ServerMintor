/**
 * Created by gaoyuan on 14-11-26.
 */

import java.sql.SQLException;

/**
 * Created by gaoyuan on 14-11-25.
 */

public class DealGetRequest {
    public static String getInfo(String order) throws SQLException {
        if (order.equals("BaseInfo")){
            return getClientBaseInfo();
        }
        else if(order.equals("CpuInfo")){
            return getCpuInfo();
        }
        else if(order.equals("MemInfo")){
            return getMemInfo();
        }
        else if (order.equals("CpuRate")){
            return getCpuRate();
        }
        else if (order.equals("NetWorkInfo")){
            return getNetWorkInfo();
        }
        else if(order.equals("DiskIO")){
            return getDiskIO();
        }
        else{
            return "No info";
        }
    }
    public static String getClientBaseInfo() throws SQLException {
        return StoreToDatabase.find("BaseInfo", "clientList");
    }
    public static String getCpuInfo() throws SQLException {
        return StoreToDatabase.find("CpuInfo", "clientList");
    }
    public static String getMemInfo() throws SQLException{
        return StoreToDatabase.find("MemInfo", "MonitorInformation");
    }
    public static String getCpuRate() throws SQLException{
        return StoreToDatabase.find("Cpurate", "MonitorInformation");
    }
    public static String getNetWorkInfo() throws SQLException{
        return StoreToDatabase.find("NetWorkInfo", "MonitorInformation");
    }
    public static String getDiskIO() throws SQLException{
        return StoreToDatabase.find("DiskIO", "MonitorInformation");
    }

}

