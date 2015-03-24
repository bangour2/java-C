import java.util.Scanner;
public class poker_Slalom_solution {
    public static void main(String args[] ) throws Exception {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT */
        
        Scanner sc = new Scanner(System.in);
        
        String[] rank = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
        String[] suit = {"H", "C", "D", "S"};  
        
        System.out.println("Input: ");
       String input = sc.nextLine();
      
      // input = "ah, 6h, 2h, 9h, th";
      // input = "ac, ah, ah, ah, th";
      // input = "ac, ah, ah, kh, th";
      // input = "ac, kh, qh, th, 4h";
      // input = "2h, 3c, 4d, 5s, 6s";
      // input = "2c, 3c, 4c, 5c, 6c";
      // input = "8d, 8s, 8d, ah, ah";
      // input = "kh, kh, 8d, 8d, ah";
      // input = "ac, kh, qh, th, mh";
       String output = null;
        
        input =  input.replace(",", "");
        input =  input.replace(" ", "");
        input =  input.replace("  ", "");        
        
        int max = 5;
        String[] combination_1 = new String[max];
        String[] combination_2 = new String[max];        
      
        int count = 1, count_ = 2, num = 0, num_ = 1;
        for(int i = 0; i< max; i++){
            combination_1[i] = input.substring(num, num_);
             combination_2[i] = input.substring(count, count_);

             count+=2; count_+=2; num+=2; num_+=2;}
        
        String rank_ = "";
        String suit_ = "";
        
        for(int i =0; i< rank.length; i++){
        	rank_ = rank[i] + rank_;}
           
        for(int i =0; i< suit.length; i++){
        	suit_ = suit[i] + suit_;}
        
        count = 1; count_ = 1; num = 1;
        int[] pair = new int[max];   
        
        for(int i = 0; i < max; i++){
        	if(i == max-1){break;}
        	
        	if(!Character.isLetter(combination_1[0].charAt(0)) && !Character.isLetter(combination_1[1].charAt(0))
        	&& !Character.isLetter(combination_1[2].charAt(0)) && !Character.isLetter(combination_1[3].charAt(0))
        	&& !Character.isLetter(combination_1[4].charAt(0))){
        if(Integer.parseInt(combination_1[i])==Integer.parseInt(combination_1[i+1])-1 || 
           Integer.parseInt(combination_1[i]) -1 ==Integer.parseInt(combination_1[i+1]) )
        	num++;}
        
        	for(int j = i+1; j< max; j++){
    	if(combination_1[i].equals(combination_1[j]))
    		    pair[i]++;}
        
        if(combination_2[i].equals(combination_2[i+1]))
        		count_++;}
        
        count = 0;
        for(int i =0; i < max; i++){
          count +=pair[i];}
            
        	if(num !=5 && count_ == 5){output = "flush";}      	
        	else if(count == 6){output = "four of a kind";}
        	else if(count == 1){output = "one pair";}
        	else if(count == 3){output = "three of a kind";}
         	else if(num == 5 && count_ != 5){output = "straight";}
        	else if(num == 5 && count_ == 5){output = "straight flush";}
        	else if(count == 4){output = "full house";}
        	else if(count == 2){output = "two pair";}
        	else {output = "high card";}

        	
         for(int i = 0; i < max; i++){	
        	 if(!rank_.contains(combination_1[i].toUpperCase())){output = "invalid output "+combination_1[i];}
        	 if(!suit_.contains(combination_2[i].toUpperCase())){output = "invalid output "+combination_2[i];}
         }
  
         System.out.println("Output: "+output);        
        
    }}