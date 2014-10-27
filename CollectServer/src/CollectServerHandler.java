import com.mypackage.MyPackage;
import io.netty.channel.ChannelHandlerAdapter;
import io.netty.channel.ChannelHandlerContext;

/**
 * Created by gaoyuan on 14-10-27.
 */
public class CollectServerHandler extends ChannelHandlerAdapter{
    public void channelRead(ChannelHandlerContext ctx,  MyPackage.InfoPackage msg) {
        System.out.println("The Type is " + msg.getInfoTypes());
        System.out.println("The Len is " + msg.getInfoLen());
        System.out.println("The Data is " + msg.getInfoData());
        ctx.write(msg.getInfoTypes());

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
