import io.netty.buffer.ByteBuf;
import io.netty.channel.*;
import io.netty.handler.codec.http.*;
import io.netty.handler.codec.http.HttpResponse;
import io.netty.handler.codec.http.multipart.*;
import io.netty.handler.codec.http.multipart.HttpPostRequestDecoder.EndOfDataDecoderException;
import io.netty.handler.codec.http.multipart.HttpPostRequestDecoder.ErrorDataDecoderException;
import io.netty.handler.stream.ChunkedFile;
import io.netty.util.CharsetUtil;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.net.URI;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import static io.netty.buffer.Unpooled.copiedBuffer;
import static io.netty.handler.codec.http.HttpHeaders.Names.*;
import static io.netty.handler.codec.http.HttpVersion.HTTP_1_1;
import static io.netty.handler.codec.http.HttpResponseStatus.OK;
import static io.netty.handler.codec.http.HttpHeaders.isKeepAlive;

/**
 * Created by gaoyuan on 14-10-26.
 */
public class HttpRequestHandler extends SimpleChannelInboundHandler<HttpObject> {

    private HttpRequest request;

    private boolean readingChunks;

    private static final HttpDataFactory factory = new DefaultHttpDataFactory(DefaultHttpDataFactory.MINSIZE); //Disk

    private HttpPostRequestDecoder decoder;

    @Override
    public void channelInactive(ChannelHandlerContext ctx) throws Exception {
        if (decoder != null) {
            decoder.cleanFiles();
        }
    }

    public void messageReceived(ChannelHandlerContext ctx, HttpObject msg) throws Exception {
        if (msg instanceof HttpRequest) {
            HttpRequest request = this.request = (HttpRequest) msg;
            URI uri = new URI(request.getUri());
            if (uri.getPath().equals("/favicon.ico")) {
                return;
            }
            if (uri.getPath().equals("/")) {
                System.out.println("Here");
                writePage(ctx);
                return;
            }

            if (request.getMethod().equals(HttpMethod.GET)){

            }
        }

        if (decoder != null) {
            if (msg instanceof HttpContent) {
                HttpContent chunk = (HttpContent) msg;
                try {
                    decoder.offer(chunk);
                } catch (ErrorDataDecoderException e1) {
                    e1.printStackTrace();
                    ctx.channel().close();
                    return;
                }
                try {
                    while (decoder.hasNext()) {
                        InterfaceHttpData data = decoder.next();
                        if (data != null) {
                            try {
                   //             writeHttpData(data);
                            } finally {
                                data.release();
                            }
                        }
                    }
                } catch (EndOfDataDecoderException e1) {
                    ;
                }

                if (chunk instanceof LastHttpContent) {
                     writePage(ctx);
                    readingChunks = false;
                    reset();
                }
            }
        }
    }

    private void writeString(ChannelHandlerContext ctx) {
        ByteBuf buf = copiedBuffer("<html>\n <body>\n <h1>Hi Zhanyongjun</h1>\n\n<p>My {'hellok': 'world'}.</p>\n\n</body>\n </html>".toString(), CharsetUtil.UTF_8);
        FullHttpResponse response = new DefaultFullHttpResponse(
                HttpVersion.HTTP_1_1, HttpResponseStatus.OK, buf);
        response.headers().set(CONTENT_TYPE, "text/html; charset=UTF-8");
        response.headers().set(CONTENT_LENGTH, buf.readableBytes());
        ctx.channel().writeAndFlush(response);
    }
    private void reset() {
        request = null;
        // destroy the decoder to release all resources
        decoder.destroy();
        decoder = null;
    }
    private void writePage(ChannelHandlerContext ctx) throws IOException {
        boolean keepAlive = isKeepAlive(request);
        if ("/".equals(request.getUri())) {
            String info = "";
            System.out.println("Openfile");
            RandomAccessFile raf = new RandomAccessFile("/home/gaoyuan/MyStation/index.html", "r");
            MappedByteBuffer out = raf.getChannel().map(FileChannel.MapMode.READ_ONLY, 0, raf.length());
            for (int i = 0; i < raf.length(); i++){
                byte tmp = out.get(i);
                System.out.print((char)tmp);
                info += (char)tmp;
            }
            ByteBuf buf = copiedBuffer(info, CharsetUtil.UTF_8);
            HttpResponse response = new DefaultFullHttpResponse(HTTP_1_1, OK, buf);

            try {
                if (keepAlive){
                    response.headers().setKeepAlive(response, true);
                }

                long fileLength = raf.length();
                response.headers().set(HttpHeaders.Names.CONTENT_LENGTH, String.valueOf(fileLength));
                ctx.channel().writeAndFlush(response);

                if (!request.getMethod().equals(HttpMethod.HEAD)) {
                    ctx.channel().write(new ChunkedFile(raf, 0, fileLength, 8192));//8kb
                }
            }catch (Exception e2) {
            e2.printStackTrace();

            } finally {
                if (keepAlive) {
                    System.out.println("keppLive");
                }
                if (!keepAlive) {
                    System.out.println("Death");
                }
            }
        }
    }
}