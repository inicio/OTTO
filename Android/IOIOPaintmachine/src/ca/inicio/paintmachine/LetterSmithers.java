package ca.inicio.paintmachine;

public class LetterSmithers {
	public String s;
	public int cursor;
	public int currentLetter;
	private int letterCode;
	private int index;

	LetterSmithers() {
		
	}
	public void setString(String s){
		this.s = s;
	}
	public void setLetterCode(int index) {
		this.index = index;
		char[] charArray = new char[s.length()];

		for (int i = 0; i < s.length(); i++) {
			charArray[i] = s.charAt(i);
		}
		
		if (cursor > charArray.length) {
			index = 0;
		}
		
		letterCode = ((int) charArray[cursor]) - 65;

	}
	public int getLetterCode(){
		return letterCode;
	}

}
