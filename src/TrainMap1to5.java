import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.Charset;


public class TrainMap1to5 {

	public void result(){
	      int y = 0;
	      String[] box = new String[1000];
	      String line;
	      
	      try{
	         // create new file input stream
	         InputStream fis = new FileInputStream("C:/Users/bango_000/Downloads/input.txt");
	         InputStreamReader isr = new InputStreamReader(fis, Charset.forName("UTF-8"));
	         BufferedReader br = new BufferedReader(isr);
	         
	         // read till the end of the file
	         while((line = br.readLine()) != null)
	         {
	        	line=line.replaceAll("[/-]", ""); //get rid of symbols such as -
	            box[y] = line; y++;}
	      }catch(Exception ex){
	         // if any error occurs
	         ex.printStackTrace();//traceback error
	      }finally{}

	      int one_five = 0, m=1, skip = 0;	      
	      String [] hold = {"AB", "BC", "CD", "DC", "DE", "AD", "CE", "EB", "AE"};
	      
	      String hold2 = "ABBCCDDCDEADCEEBAE";
	      
	      String[] hold_temp = new String[hold.length];
	  
	    	  //reinitialiaze variables
	    	  one_five = 0;	    	 
	    	  hold_temp = new String[hold.length];
    	      for(int x =0; x< box[x].length(); x++) {
    	    	  
    	      if(m == 6){break;}	  
	    	  
	    	  if(box[x]==null){break;}
	    	  //map letters to their values 
	    	  if(box[x].contains(hold[0])) one_five += 5;		    				   
   		  if(box[x].contains(hold[1])) one_five += 4; 
   	      if(box[x].contains(hold[2])) one_five += 8; 
   	      if(box[x].contains(hold[3])) one_five += 8; 		    	      
   	      if(box[x].contains(hold[4])) one_five += 6; 
   	      if(box[x].contains(hold[5])) one_five += 5; 
   		  if(box[x].contains(hold[6])) one_five += 2; 
   		  if(box[x].contains(hold[7])) one_five += 3; 
   		  if(box[x].contains(hold[8])) one_five += 7;
   		  
   		  //grouping letters in text by 2
   		  for(int r =0; r<box[x].length(); r++){
   			  
   			  if(r == box[x].length() -1){break;}
   			  hold_temp[r] = box[x].charAt(r)+""+box[x].charAt(r+1);}
   		  
   		  //compare letters to given letters
             for(int r =0; r<box[x].length()-1; r++){			  
           	  if(!(hold2.contains(hold_temp[r]))) {skip = 1;}}
   		  
   
   		  
   		  if(skip == 0){System.out.println("output #"+(m)+": "+one_five); m++;}
   		  if(skip == 1) {System.out.println("output #"+(m)+": NO SUCH ROUTE"); m++;}   	  
    		  one_five = 0;}
	}
}
