# Ring (Research Bing)
Current State: *ALPHA*

## To compile:
<code>make</code>
<code>./run</code>

##Status of Ring
- Currently no matter the word you enter, all that will print is the PageRank and Hits data for the current subset of articles.
- This is intentional, due to the fact we still have to read the ids for each word from our BST.
  - Hope to complete on Monday.
- A "GatherData.c" exists and is used to generate the metadata.
  - There will be no use of this as of now due to the existing bugs, but will exist in next release.

##Known Bugs
- Mild lack of support for IDs that countain words, need to just keep them as char instead of atof().
- Issues within the Alphabetized.txt file that occured when an abstract was too long to fit in the buffer.
  -This causes every other implementation to not work, after this is fixed, GatherData.c "should" be fully functional.

##arXiv Files
BST.txt - Holds the word occuring in every abstract in the subset, and the id that uses the word in the articles abstract.
FinalList.txt - Ignore for now.
IDs.txt - Contains the IDs for the subset used in the demo.
List_of_Abstracts.txt - As the name states, but one abstract is not there.
temp_citations.txt - Used for demo, had to be created due to no citations within first 10 articles.
Words.txt - Empty for now.
WordsFinal.txt - Contains all of the words that exist in each abstract given, common words are removed 
*Logo that MD won't use*

##Future Outlook
With all honesty, we are extremely close to a working search engine that is works on a number of documents the user specifies.  If there is an extended due date, we pledge to have a working version by then.  Overall, we have put our blood, sweat, and tears into this project.  We estimate an ~6 hours a day for two weeks straight for the both of us.  We are exhausted, but also hungry to finish the project.  Furthermore, we want to rest up for a day, then have a working version ready.

##Example Run
Get the users search:
--> sdfdf

If a cla -verbose=on is used, display the status of the search.

============================================
Return Results Here!
adj matrix
0.00 1.00 1.00 0.00 0.00 0.00 0.00 0.00 1.00
0.00 0.00 0.00 0.00 0.00 1.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 1.00 0.00 1.00 0.00
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
1.00 0.00 0.00 0.00 0.00 1.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 1.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 1.00 1.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00

----------------------------
line 1: rowptrs, line 2: col idx, line 3: vals
0  3  4  6  6  8  8  9  11  11
1  2  8  5  5  7  0  5  5  5  6
1.000000  1.000000  1.000000  1.000000  1.000000  1.000000  1.000000  1.000000  1.000000  1.000000  1.000000
----------------------------
0 -> 1 (1.000000) 2 (1.000000) 8 (1.000000)
1 -> 5 (1.000000)
2 -> 5 (1.000000) 7 (1.000000)
3 ->
4 -> 0 (1.000000) 5 (1.000000)
5 ->
6 -> 5 (1.000000)
7 -> 5 (1.000000) 6 (1.000000)
8 ->

Page rank vector:
0.131820 0.118701 0.129304 0.081272 0.130340 0.081272 0.118701 0.127319 0.081272

Hubs vector:
1.000000 1.000000 1.000000 0.000000 1.000000 0.000000 1.000000 1.000000 0.000000
Auths vector:
1.000000 1.000000 1.000000 0.000000 0.000000 5.000000 1.000000 1.000000 1.000000
