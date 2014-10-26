import io.netty.channel.ChannelInitializer;
import io.netty.channel.ChannelPipeline;
import io.netty.channel.socket.SocketChannel;
import io.netty.handler.codec.http.HttpContentCompressor;
import io.netty.handler.codec.http.HttpRequestDecoder;
import io.netty.handler.codec.http.HttpResponseEncoder;
import io.netty.handler.stream.ChunkedWriteHandler;
/**
 * Created by gaoyuan on 14-10-26.
 */

public class HttpServerInitializer extends ChannelInitializer<SocketChannel> {
    @Override
    public void initChannel (SocketChannel ch) throws Exception {
        ChannelPipeline pipeline = ch.pipeline();
        pipeline.addLast("decoder", new HttpRequestDecoder());
        pipeline.addLast("encoder", new HttpResponseEncoder());
   //     pipeline.addLast("chunkedWriter", new ChunkedWriteHandler());
        pipeline.addLast("deflater", new HttpContentCompressor());
        pipeline.addLast("handler", (io.netty.channel.ChannelHandler) new HttpRequestHandler());

        System.out.println("Initializer OK");
    }
}