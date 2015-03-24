public class TrainMap10 {

    public int[][] map = { 
            {-1, 5, -1, 5, 7}, 
            {-1, -1, 4, -1, -1},
            {-1, -1, -1, 8, 2},
            {-1, -1, 8, -1, 6},
            {-1, 3, -1, -1, -1},
    };
    
    int count = 0;
    public void result(String end, String path, int cost) {
    	if (cost >= 30)
            return ;     

        if (cost > 0 && path.endsWith(end)) {
            //System.out.println(path + ", " + cost);
        	count++;}
        


        char lastChar = path.charAt(path.length() - 1);
        int lastNodeIndex = lastChar - 'A';

        for (int i = 0; i < map[lastNodeIndex].length; i++) {
            char newChar = (char) (i + 'A');
            int newCost = map[lastNodeIndex][i];
            if (newCost > 0) {
                result(end, path + newChar, cost + newCost);
            }
        }}
    
   public int result(){return count;}
}
