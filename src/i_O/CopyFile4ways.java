package i_O;
import java.io.*;
import java.nio.channels.FileChannel;
import java.nio.file.Files;
//import org.apache.commons.io.FileUtils;

public class CopyFile4ways {
	public static void main(String[] args) throws InterruptedException,
		            IOException {
		
	File source = new File(args[0]);
				        File dest = new File(args[1]);
 
    // copy file using FileStreams
    long start = System.nanoTime();
    long end;
    copyFileUsingFileStreams(source, dest);
    System.out.println("Time taken by FileStreams Copy = "
            + (System.nanoTime() - start));
				 
    // copy files using java.nio.FileChannel
    source = new File(args[2]);
    dest = new File(args[3]);
    start = System.nanoTime();
    copyFileUsingFileChannels(source, dest);
    end = System.nanoTime();
    System.out.println("Time taken by FileChannels Copy = " + (end - start));
 
        // copy file using Java 7 Files class
    source = new File(args[4]);
    dest = new File(args[5]);
    start = System.nanoTime();
    copyFileUsingJava7Files(source, dest);
    end = System.nanoTime();
    System.out.println("Time taken by Java7 Files Copy = " + (end - start));
 
        // copy files using apache commons io
    source = new File(args[6]);
    dest = new File(args[7]);
    start = System.nanoTime();
    //copyFileUsingApacheCommonsIO(source, dest);
    end = System.nanoTime();
    System.out.println("Time taken by Apache Commons IO Copy = "
            + (end - start));
 
    }
 
    private static void copyFileUsingFileStreams(File source, File dest)
            throws IOException {
        InputStream input = null;
        OutputStream output = null;
        
        try {//option1.
            input = new FileInputStream(source);
            output = new FileOutputStream(dest);
            byte[] buf = new byte[1024];
            int bytesRead;
            while ((bytesRead = input.read(buf)) > 0) {
                output.write(buf, 0, bytesRead);
            }
            
           /* try {//option1.
	            input = new FileInputStream(source);
	            output = new FileOutputStream(dest);
	            do { 
	            i = fin.read(); 
	            if(i != -1) fout.write(i); }
	             while(i != -1); 
	            }*/
            
        } finally {
            input.close();
            output.close();
        }
    }
 
    private static void copyFileUsingFileChannels(File source, File dest)
            throws IOException {
        FileChannel inputChannel = null;
        FileChannel outputChannel = null;
        try {
            inputChannel = new FileInputStream(source).getChannel();
            outputChannel = new FileOutputStream(dest).getChannel();
            outputChannel.transferFrom(inputChannel, 0, inputChannel.size());
        } finally {
            inputChannel.close();
            outputChannel.close();
    }
    }
 
    private static void copyFileUsingJava7Files(File source, File dest)
            throws IOException {
        Files.copy(source.toPath(), dest.toPath());
    }
 
//		    private static void copyFileUsingApacheCommonsIO(File source, File dest)
//		            throws IOException {
//		        FileUtils.copyFile(source, dest);}
}
