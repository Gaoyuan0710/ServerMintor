import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.*;
import io.netty.channel.local.LocalChannel;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioServerSocketChannel;


/**
 * Created by gaoyuan on 14-10-27.
 */
public final class CollectServer {
    static final int PORT = Integer.parseInt(System.getProperty("port", "8089"));


    public static void CollectStart() {
        EventLoopGroup bossGroup = new NioEventLoopGroup();
        EventLoopGroup workerGroup = new NioEventLoopGroup();
        try {
            ServerBootstrap collect = new ServerBootstrap();
            collect.group(bossGroup, workerGroup)
                    .channel(NioServerSocketChannel.class)
                    .option(ChannelOption.SO_BACKLOG, 100)
                    .childHandler(new CollectServerInitializer());

            ServerBootstrap webServer = new ServerBootstrap();
            webServer.group(bossGroup, workerGroup)
                    .channel(NioServerSocketChannel.class)
                    .childHandler(new HttpServerInitializer());


            ChannelFuture f = collect.bind(PORT).sync();
            Channel ch = webServer.bind(8080).sync().channel();



            ch.closeFuture().sync();
            f.channel().closeFuture().sync();
        } catch (InterruptedException e) {
            e.printStackTrace();
            ErrorLog.writeToFile(e.toString());
        } finally {
            bossGroup.shutdownGracefully();
            workerGroup.shutdownGracefully();
        }
    }

    public static void main(String[] args) {
        CollectStart();
    }
}
