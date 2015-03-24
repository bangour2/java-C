package i_O;

import java.awt.Image;
	import java.io.File;
	import java.io.IOException;
	 
	import javax.imageio.ImageIO;
	 
	public class ReadImageFromFile {
	 
	    public static void main(String[] args) throws IOException {
	 
	        // input image file
	        File file = new File(args[0]);
	        Image image = ImageIO.read(file);
	 
	        int width = image.getWidth(null);
	        int height = image.getHeight(null);
	 
    }}