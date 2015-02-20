import io.netty.buffer.ByteBuf;
import io.netty.channel.*;
import io.netty.handler.codec.http.*;
import io.netty.handler.codec.http.HttpResponse;
import io.netty.handler.codec.http.multipart.*;
import io.netty.handler.codec.http.multipart.HttpPostRequestDecoder.ErrorDataDecoderException;
import io.netty.handler.stream.ChunkedFile;
import io.netty.util.CharsetUtil;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.util.*;

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
    private final StringBuilder responseContent = new StringBuilder();
    private HttpPostRequestDecoder decoder;
    private static final HttpDataFactory factory =
            new DefaultHttpDataFactory(DefaultHttpDataFactory.MINSIZE);
    private boolean readingChunks;

    static {
        DiskFileUpload.deleteOnExitTemporaryFile = true; // should delete file
        // on exit (in normal
        // exit)
        DiskFileUpload.baseDirectory = null; // system temp directory
        DiskAttribute.deleteOnExitTemporaryFile = true; // should delete file on
        // exit (in normal exit)
        DiskAttribute.baseDirectory = null; // system temp directory
    }

    @Override
    public void channelInactive(ChannelHandlerContext ctx) throws Exception {
        if (decoder != null) {
            decoder.cleanFiles();
        }
    }

    @Override
    public void messageReceived(ChannelHandlerContext ctx, HttpObject msg) throws Exception {
        if (msg instanceof HttpRequest) {
            HttpRequest request = this.request = (HttpRequest) msg;
            if("/".equals(request.getUri())){
                writePage(ctx);
                return;
            }
            if (request.getMethod() == HttpMethod.GET) {
                QueryStringDecoder decoder = new QueryStringDecoder(request.getUri());
                System.out.println(request.getUri());
                Map<String, List<String>> parame = decoder.parameters();
                if (parame == null) {
                    return;
                }
                List<String> actionlist = parame.get("action");
                List<String> serverListId = parame.get("serverId");
                List<String> parameter = new ArrayList<String>();

                if (parame.containsKey("parameter")) {
                    System.out.println("You");
                   parameter  = parame.get("parameter");
                }
                else {
                    System.out.println("Mei you");
                }
                int i = 0;
                String data = "[";

                for (String sourceRequest : actionlist) {
                    if (sourceRequest != null && !sourceRequest.equals("")) {
                        if (parameter.isEmpty()) {

                            data += DealGetRequest.getInfo(Integer.valueOf(serverListId.get(i)), sourceRequest, "");
                        }
                        else {
                            data += DealGetRequest.getInfo(Integer.valueOf(serverListId.get(i)), sourceRequest, parameter.get(i));
                        }
                        data += ",";
                    }
                    i++;
                }
                data = data.substring(0, data.length() - 1);
                data += "]";
                ByteBuf buf = copiedBuffer(data, CharsetUtil.UTF_8);
                FullHttpResponse response = new DefaultFullHttpResponse(
                        HttpVersion.HTTP_1_1, HttpResponseStatus.OK, buf);
                response.headers().set(CONTENT_TYPE, "text/html; charset=UTF-8");
                response.headers().set(CONTENT_LENGTH, buf.readableBytes());
                response.headers().set(ACCESS_CONTROL_ALLOW_ORIGIN, "*");
                response.headers().set(CACHE_CONTROL, "private, must-revalidate");
                ctx.channel().writeAndFlush(response);
            } else if (request.getMethod() == HttpMethod.POST){
                ErrorLog.writeToFile("Get Post Request");
            }

            {
                decoder = new HttpPostRequestDecoder(factory, request);
                readingChunks = HttpHeaders.isTransferEncodingChunked(request);

            }
        }

        if (decoder != null)

        {
            if (msg instanceof HttpContent) {
                HttpContent chunk = (HttpContent) msg;

                try {
                    decoder.offer(chunk);
                } catch (ErrorDataDecoderException e1) {
                    e1.printStackTrace();
                }
                List<InterfaceHttpData> dataList = decoder.getBodyHttpDatas();

                for (InterfaceHttpData data : dataList) {
                    if (data.getHttpDataType() == InterfaceHttpData.HttpDataType.Attribute) {
                        Attribute attribute = (Attribute) data;
                        System.out.println(attribute.getHttpDataType().name() + ":" + attribute.toString());
                    }
                }
                if (chunk instanceof LastHttpContent) {
                    writeResponse(ctx.channel());
                    readingChunks = false;
                    reset();
                }
            }
        }
    }
    private void reset() {
        request = null;
        decoder.destroy();
        decoder = null;
    }

    private void writeResponse(Channel channel) {
        // Convert the response content to a ChannelBuffer.
        ByteBuf buf = copiedBuffer(responseContent.toString(), CharsetUtil.UTF_8);
        responseContent.setLength(0);

        // Decide whether to close the connection or not.
        boolean close = request.headers().contains(CONNECTION, HttpHeaders.Values.CLOSE, true)
                || request.getProtocolVersion().equals(HttpVersion.HTTP_1_0)
                && !request.headers().contains(CONNECTION, HttpHeaders.Values.KEEP_ALIVE, true);

        // Build the response object.
        FullHttpResponse response = new DefaultFullHttpResponse(HttpVersion.HTTP_1_1, HttpResponseStatus.OK, buf);
        response.headers().set(CONTENT_TYPE, "text/plain; charset=UTF-8");

        if (!close) {
            // There's no need to add 'Content-Length' header
            // if this is the last response.
            response.headers().set(CONTENT_LENGTH, buf.readableBytes());
        }

        Set<Cookie> cookies;
        String value = request.headers().get(COOKIE);
        if (value == null) {
            cookies = Collections.emptySet();
        } else {
            cookies = CookieDecoder.decode(value);
        }
        if (!cookies.isEmpty()) {
            // Reset the cookies if necessary.
            for (Cookie cookie : cookies) {
                response.headers().add(SET_COOKIE, ServerCookieEncoder.encode(cookie));
            }
        }
        // Write the response.
        ChannelFuture future = channel.writeAndFlush(response);
        // Close the connection after the write operation is done if necessary.
        if (close) {
            future.addListener(ChannelFutureListener.CLOSE);
        }
    }

    private void writePage(ChannelHandlerContext ctx) throws IOException {
        boolean keepAlive = isKeepAlive(request);
        if ("/".equals(request.getUri())) {
            String info = "";
            RandomAccessFile raf = new RandomAccessFile("/home/gaoyuan/MyStation/index.html", "r");
            MappedByteBuffer out = raf.getChannel().map(FileChannel.MapMode.READ_ONLY, 0, raf.length());
            for (int i = 0; i < raf.length(); i++) {
                byte tmp = out.get(i);
                info += (char) tmp;
            }
            ByteBuf buf = copiedBuffer(info, CharsetUtil.UTF_8);
            HttpResponse response = new DefaultFullHttpResponse(HTTP_1_1, OK, buf);

            try {
                if (keepAlive) {
                    response.headers().setKeepAlive(response, true);
                }

                long fileLength = raf.length();
                response.headers().set(HttpHeaders.Names.CONTENT_LENGTH, String.valueOf(fileLength));
                ctx.channel().writeAndFlush(response);

                if (!request.getMethod().equals(HttpMethod.HEAD)) {
                    ctx.channel().write(new ChunkedFile(raf, 0, fileLength, 8192));//8kb
                }
            } catch (Exception e2) {
                ErrorLog.writeToFile(e2.toString());
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