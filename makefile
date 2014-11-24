dict:
	g++ ./dictionary/dictionary.cpp ./dictionary/main.cpp -o dict
clean:
	rm dict
archive:
	tar cvf ../CS2010_4374851_Assign02.tar .
