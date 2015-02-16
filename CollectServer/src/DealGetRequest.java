/**
 * Created by gaoyuan on 14-11-26.
 */

import io.netty.buffer.Unpooled;
import io.netty.util.CharsetUtil;

import java.sql.SQLException;

/**
 * Created by gaoyuan on 14-11-25.
 */

public class DealGetRequest {
    public static String getInfo(int clientID, String order, String parameter) throws SQLException {
        if (order.equals("getBaseInfo")){
            return getClientBaseInfo(clientID);
        }
        else if(order.equals("getCpuInfo")){
            return getCpuInfo(clientID);
        }
        else if(order.equals("getMemInfo")){
            return getMemInfo(clientID);
        }
        else if (order.equals("getCpuRate")){
            return getCpuRate(clientID);
        }
        else if (order.equals("getNetWorkInfo")){
            return getNetWorkInfo(clientID);
        }
        else if(order.equals("getDiskIO")){
            return getDiskIO(clientID);
        }
        else if(order.equals("getIp")){
            return getIp(clientID);
        }
        else if(order.equals("getPidsSortByCpu")){
            return getPidsSortByCpu(clientID);
        }
        else if(order.equals("getPidsSortByMem")){
            return getPidsSortByMem(clientID);
        }
        else if(order.equals("getNetWorkNums")){
            return getNetWorkNums(clientID);
        }

        else if(order.equals("updateTime")){
            System.out.println("ssssssssssssssssssssss");
            return getOrders("updateTime", clientID, parameter);
        }
        else if(order.equals("killPro")){
            return getOrders("killPro", clientID, parameter);
        }
        else if(order.equals("restart")){
            return getOrders("restart", clientID, parameter);
        }

        else{
            return "No info";
        }
    }
    public static String getClientBaseInfo(int clientID) throws SQLException {
        return StoreToDatabase.findBaseInfo(clientID);
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
        return StoreToDatabase.findDiskIo("IOInfo", "MonitorInformation", clientID);
    }
    public static String getIp(int clientID) throws SQLException{
        return StoreToDatabase.find("Ip", "clientList", clientID);
    }
    public static String getPidsSortByCpu(int clientID) throws SQLException{
        return StoreToDatabase.findProInfo("ProSortByCpu", "MonitorInformation", clientID);

    }
    public static String getPidsSortByMem(int clientID) throws SQLException{
        return StoreToDatabase.findProInfo("ProSortByMem", "MonitorInformation", clientID);

    }
    public static String getNetWorkNums(int clientID) throws SQLException{
        return StoreToDatabase.findNetWorkNums("NetWorkNums", "MonitorInformation", clientID);
    }

    public static String getOrders(String order, int clientID, String parameter) {
        String sendOrder = "";
        sendOrder += order;
        sendOrder += "&";
        sendOrder += clientID;
        sendOrder += "&";
        sendOrder += parameter;

        if (order.equals("restart") || order.equals("killPro")){
            if (parameter.isEmpty() ){//!parameter.equals("8541a5ab59c0e5436c2d7b39933bbc65")){
                return "invaild passwd";
            }
        }
        if (order.equals("updateTime")){
            System.out.println(parameter);
            if (parameter.isEmpty() ||Integer.valueOf(parameter) < 0 ){
                return "wrong parameter";
            }


        }
        OnLineClient.channelGroup.write(Unpooled.copiedBuffer(sendOrder, CharsetUtil.UTF_8));
        OnLineClient.channelGroup.flush();




    //    TempData tempData = TempData.getInstance();
    //    System.out.println(tempData.getValue("NetWorkNums"));
        return "I have get your order, Please wait";
    }

}

