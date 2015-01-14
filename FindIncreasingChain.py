import re
#Denis Kazakov
#findin longest chain of words, where each consecutive word has the same letters as the previous one, plus one more.
#3 maximum chain of words:
#1: ['er', 'red', 'dree', 'cered', 'crewed', 'wrecked', 'rockweed', 'rockweeds', 'recrudesce', 'recrudesced', 'underclothes', 'depreciations', 'decrepitations']
#2: ['er', 'rem', 'derm', 'demur', 'dumber', 'umbered', 'cumbered', 'slumbered', 'maunderers', 'unearmarked', 'dramaturgies', 'determinators', 'determinatives']
#3: ['un', 'run', 'durn', 'under', 'turned', 'trudgen', 'trudgens', 'trudgeons', 'outreading', 'outdreaming', 'denaturalize', 'denaturalized', 'countershading']

words=[]
with open('/home/user/Dropbox/School/csci/csci-3104 algorithms/python/HW5/wordlist.txt') as qfile:
    for word in qfile:
        word = word.rstrip('\n').lower()
        words.append(word)
		#make separate wordlist and sort it by size, sort each word alphabetically
words.sort(key = lambda s: len(s))


maximum = len(words[len(words)-1]) #longest string we have
searchLength = len (words[1])
MaximumChainLength = 0
longestChainWord = [None] * 13

#OFFSETS
counter = 0
offset = [0,0] #for skipping to searchLength+1 sized strings
while (searchLength < maximum):
	while ((len(words[counter])-searchLength)==0):
			counter+=1
	offset.append(counter)
	#print offset, searchLength, offset[searchLength]
	searchLength+=1
offset.append(len(words)) #final step is the size of wordlist

#_____________________________

#function - recursive, works with given stack, to go to next level

#checks if the two words are "connected", aka have same letters but one
def checkSimilarity(word1, nextWord):
	word1 = list(word1)
	nextWord = list(nextWord)
	#print nextWord[:-1], word1
	
	for letter in word1:
		if (not(letter in nextWord)):
			return 0
		else: 
			nextWord.remove(letter)
	return 1


level = 0
printed = 0;
def recursiveFind(searchLength, level, originalWord, currentWord):
	global MaximumChainLength 
	global longestChainWord 
	global printed
	#print searchLength, originalWord, currentWord
	if (searchLength == 15 & printed == 0):
		longestChainWord[0] = originalWord
		print longestChainWord
		searchLength = 0
		printed = 1
		return None
	elif (printed ==1):
		return 
	else:
		for i in range (offset[searchLength], offset[searchLength+1]):
			#if current longest chain is smaller
			if (level>MaximumChainLength):
				longestChainWord[level] = currentWord
				MaximumChainLength = level
				print longestChainWord, MaximumChainLength
			if checkSimilarity(currentWord, words[i]):
				recursiveFind(searchLength+1, level+1, originalWord, words[i])

#MAIN
searchLength = len (words[1])
#choose which word to start with
recursiveFind(searchLength,0,words[10],words[10])
