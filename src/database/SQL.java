package database;

import java.sql.*;

public class SQL {
	
	private Connection con;
	private Statement st;
	private ResultSet rs;

	
	public SQL(){
		//execute all static method of following class
		try {
			//Class.forName("com.mysql.jdbc.Driver");
		
		con = DriverManager.getConnection("jdbc:mysql://localhost:3306/birt", 
				"root", "noble0012");
		
		st = con.createStatement();}
		catch(Exception e){System.out.println("Error "+e);}}
	
	
	public String modify(String query_){
		try{ String query =query_;
		st.executeUpdate(query);
		System.out.println("successfully modify");}
		
		catch(Exception e){System.out.println(e);}
		return null;
	}
	public String getData(String[] column, String query_){
       String email ="";
		try{ String query =query_;
		rs = st.executeQuery(query);
		
		System.out.println("Data from Database");
		while(rs.next()){		
			 email = email+ rs.getString(column[0]) +" "+rs.getString(column[1])+"\n";
		}}
		
		catch(Exception e){System.out.println("Error "+e);}
		return email;}

}
