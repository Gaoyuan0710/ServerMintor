import com.mypackage.MyPackage;
import io.netty.channel.ChannelHandlerAdapter;
import io.netty.channel.ChannelHandlerContext;
import org.json.JSONException;


/**
 * Created by gaoyuan on 14-10-27.
 */
public class CollectServerHandler extends ChannelHandlerAdapter{
    public void channelRead(ChannelHandlerContext ctx,  Object msgdata) throws Exception {
        MyPackage.InfoPackage  data = (MyPackage.InfoPackage)msgdata;

        System.out.println(data.getInfoTypes());
        System.out.println(InfoType.getInfoType(data.getInfoTypes()));
        System.out.println(data.getInfoLen());

        try {
            AnalyticalToJson.StringAnalyticalToJson(data.getInfoData());
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
