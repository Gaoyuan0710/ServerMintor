import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.Channel;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.sctp.nio.NioSctpServerChannel;
import io.netty.handler.logging.LogLevel;
import io.netty.handler.logging.LoggingHandler;


/**
 * Created by gaoyuan on 14-10-26.
 */
public class HttpServer {
    private int port;
    public HttpServer(int port){
        this.port = port;
    }
   // static final boolean SSL = System.getProperty("ssl") != null;
   // static final int PORT = Integer.parseInt(System.getProperty("port", SSL ? "8443" : "8080"));
    public static void main(String[] args) {
        EventLoopGroup bossGroup = new NioEventLoopGroup();
        EventLoopGroup workerGroup = new NioEventLoopGroup();

        try{
        ServerBootstrap bootstrap = new ServerBootstrap();
            bootstrap.group(bossGroup, workerGroup)
                    .channel(NioSctpServerChannel.class)
                    .childHandler(new HttpServerInitializer());

           Channel ch = bootstrap.bind(8080).sync().channel();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            bossGroup.shutdownGracefully();
            workerGroup.shutdownGracefully();
        }

        System.out.println("" + "We are OK\n\n");
    }
}
