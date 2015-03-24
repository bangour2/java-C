package i_O;

	import java.io.IOException;
	import java.io.FileInputStream;

	public class FileInputStreamDemo {
	   public static void main(String[] args) throws IOException {
	      
	      FileInputStream fis = null;
	      int i = 0;
	      char c;
	      
	      try{
	         // create new file input stream
	         fis = new FileInputStream(args[0]);
	         
	         // read till the end of the file
	         while((i=fis.read())!=-1)
	         {
	            // converts integer to character
	            c=(char)i;
	            
	            // prints character
	            System.out.print(c);
	         }
	      }catch(Exception ex){
	         // if any error occurs
	         ex.printStackTrace();//traceback error
	      }finally{
	         
	         // releases all system resources from the streams
	         if(fis!=null)
	            fis.close();
	      }}}