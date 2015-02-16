import com.mypackage.MyPackage;
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

        System.out.println(data.getInfoTypes());
        System.out.println(InfoType.getInfoType(data.getInfoTypes()));
        System.out.println(data.getInfoLen());
        System.out.println(data.getInfoData());

        String message = "I get your message";
        System.out.println(message);

    //   ctx.write(Unpooled.copiedBuffer(message, CharsetUtil.UTF_8));
    //    ctx.flush();
        try {
           AnalyticalToJson.StringAnalyticalToJson(data.getInfoTypes(), data.getInfoData());
        } catch (Exception e) {
            e.printStackTrace();
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
