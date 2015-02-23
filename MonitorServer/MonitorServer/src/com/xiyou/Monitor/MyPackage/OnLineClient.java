package com.xiyou.Monitor.MyPackage;

import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.group.ChannelGroup;
import io.netty.channel.group.DefaultChannelGroup;
import io.netty.util.concurrent.GlobalEventExecutor;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by gaoyuan on 15-2-15.
 */
public class OnLineClient {
    public static Map<String, ChannelHandlerContext> userMap = new HashMap<String, ChannelHandlerContext>();
    public static ChannelGroup channelGroup = new DefaultChannelGroup(GlobalEventExecutor.INSTANCE);

}

