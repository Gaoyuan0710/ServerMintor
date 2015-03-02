package com.xiyou.Monitor.CollectServer;

import com.xiyou.Monitor.MyPackage.MyPackage;
import com.xiyou.Monitor.Log.ErrorLog;
import com.xiyou.Monitor.MyPackage.OnLineClient;
import com.xiyou.Monitor.ToJson.AnalyticalToJson;
import io.netty.buffer.Unpooled;
import io.netty.channel.ChannelHandlerAdapter;
import io.netty.channel.ChannelHandlerContext;
import io.netty.util.CharsetUtil;
import org.json.JSONException;


/**
 * Created by gaoyuan on 14-10-27.
 */
public class CollectServerHandler extends ChannelHandlerAdapter {
    public void channelActive(ChannelHandlerContext ctx) throws Exception {
        OnLineClient.channelGroup.add(ctx.channel());
    }
    public void channelInactive(ChannelHandlerContext ctx){
        OnLineClient.channelGroup.remove(ctx);

    }
    public void channelRead(ChannelHandlerContext ctx, Object msgdata) throws Exception {
        MyPackage.InfoPackage data = (MyPackage.InfoPackage) msgdata;

        try {
            AnalyticalToJson.StringAnalyticalToJson(data.getInfoTypes(), data.getInfoData());
        } catch (Exception e) {
            e.printStackTrace();
            ErrorLog.writeToFile(e.toString());
        }
    }

    @Override
    public void channelReadComplete(ChannelHandlerContext ctx) {
        ctx.flush();
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        cause.printStackTrace();
        ctx.close();
    }
}

