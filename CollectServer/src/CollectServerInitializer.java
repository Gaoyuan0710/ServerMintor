import com.mypackage.MyPackage;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.ChannelPipeline;
import io.netty.channel.local.LocalChannel;
import io.netty.channel.socket.SocketChannel;
import io.netty.handler.codec.protobuf.ProtobufDecoder;

/**
 * Created by gaoyuan on 14-11-17.
 */
public class CollectServerInitializer extends ChannelInitializer<SocketChannel> {
    @Override
    public void initChannel(SocketChannel ch) throws Exception {
        ChannelPipeline p = ch.pipeline();
        p.addLast("protobufDecoder", new ProtobufDecoder(MyPackage.InfoPackage.getDefaultInstance()));
        p.addLast(new CollectServerHandler());
        //p.addLast("handler", new HttpRequestHandler());
    }
}
