package database;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import tangent_line_equation.Tangent_line_equation1;

public class Main {
	
	String finalValue ="";
	static String value_="";
	static SQL conn =new SQL();
	int count = 0;
 
	
	public static void create(String query){
		query = "create table xy (id int)";
		System.out.println(conn.modify(query));
	}
	
	public static void SQL_insert(String query, String value1, String value2){

	    query = "insert into xy (date, numero) values ('"+value1+"'"+", '"+value2+"')";
		System.out.println(conn.modify(query));
	}
	
	public static String  SQL_getData(String query){
		String[] column = new String[2];
		column[0] = "date";
		column[1] = "numero";
		
		query = "select * from xy order by date";
		//System.out.println(conn.getData(column, query));
		return conn.getData(column, query);
	}
	
	public static void delete(String query){		
		query = "Delete * from xy where 1 = 1";
		System.out.println(conn.modify(query));
	}

	public static void main(String[] args) throws Exception{
		SQL_getData("");
		
		File fi=new File("C:/Users/bango_000/Downloads/output.txt");
		PrintWriter p2 = null;
	
		try {p2 = new PrintWriter(fi);}
	    catch (FileNotFoundException e1) {
		e1.printStackTrace();}
		
		p2.write(SQL_getData("")+"\n");
		p2.close();
		
		
	}}
