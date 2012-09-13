//Alex Wellock
import java.io.IOException;
import java.io.StringReader;
public class Test {
	
	public static void main(String[] args) throws IOException {
		String input = "/* This is just a simple program with **objects **/ */\n" +
						"class Animal {\n"+
						 " int height;\n" +
						 " double weight;\n" +
						 "  void Eat() { weight = weight * 2.0;}\n" +
						"}\n" +
						"class Cow extends Animal {\n" +
						  "string name;\n" +
						  "void Moo() { }\n" +
						"}\n" +
						"void main() {\n" +
						"  class Cow betsy;\n" +
						"  betsy = new Cow;\n" +
						"  betsy.height = 0xa2;\n" +
						"  betsy.weight = 1.456;\n" +
						"  besty.name = \"Betsy\";\n" +
						"  betsy.Moo(); // Go, Betsy!\n" +
						"}";
		Lexer lexer = new Lexer(new StringReader(input));
		for(int i = 0; i < 120; i++)
			lexer.next_token();
	}

}
