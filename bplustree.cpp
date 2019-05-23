#include<bits/stdc++.h>
using namespace std;

#define MAX 50
int numberOfPointers;

struct Block{
    int tNodes;
    Block *parentBlock;
    int value[MAX];
    Block *childBlock[MAX];
    Block *brotherBlock;
    Block(){
        tNodes = 0;
        parentBlock = NULL;
        brotherBlock = NULL;
        for(int i=0; i<numberOfPointers+1; i++){
            value[i] = INT_MAX;
            childBlock[i] = NULL;
        }
    }
};
Block *rootBlock;

void split(Block *curBlock,bool isleaf){
    int x, i, j;
    if(numberOfPointers%2)
        x = (numberOfPointers+1)/2;
    else x = numberOfPointers/2;

    Block *rightBlock = new Block();

    curBlock->tNodes = x;
    if(isleaf)
    rightBlock->tNodes = numberOfPointers-x;
    else
    rightBlock->tNodes = numberOfPointers-x-1;
    rightBlock->parentBlock = curBlock->parentBlock;


    for(i=x, j=0; i<=numberOfPointers; i++, j++){
        rightBlock->value[j] = curBlock->value[i];
        rightBlock->childBlock[j] = curBlock->childBlock[i];
        curBlock->value[i] = INT_MAX;
        if(i!=x)curBlock->childBlock[i] = NULL;
    }
    int val = rightBlock->value[0];
    if(!isleaf)
    {memcpy(&rightBlock->value, &rightBlock->value[1], sizeof(int)*(rightBlock->tNodes+1));
    memcpy(&rightBlock->childBlock, &rightBlock->childBlock[1], sizeof(rootBlock)*(rightBlock->tNodes+1));
    }

    for(i=0;curBlock->childBlock[i]!=NULL;i++){
        curBlock->childBlock[i]->parentBlock = curBlock;
    }
    for(i=0;rightBlock->childBlock[i]!=NULL;i++){
        rightBlock->childBlock[i]->parentBlock = rightBlock;
    }

    if(isleaf)
        {   Block* temp=curBlock->brotherBlock;
            curBlock->brotherBlock = rightBlock;
            rightBlock->brotherBlock=temp;
        }

    if(curBlock->parentBlock==NULL){
        Block *parentBlock = new Block();
        parentBlock->parentBlock = NULL;
        parentBlock->tNodes=1;
        parentBlock->value[0] = val;
        parentBlock->childBlock[0] = curBlock;
        parentBlock->childBlock[1] = rightBlock;
        curBlock->parentBlock = rightBlock->parentBlock = parentBlock;
        rootBlock = parentBlock;
        return;
    }
    else{
        curBlock = curBlock->parentBlock;

        Block *newChildBlock = new Block();
        newChildBlock = rightBlock;

        for(i=0; i<=curBlock->tNodes; i++){
            if(val < curBlock->value[i]){
                swap(curBlock->value[i], val);
            }
        }

        curBlock->tNodes++;

        for(i=0; i<curBlock->tNodes; i++){
            if(newChildBlock->value[0] < curBlock->childBlock[i]->value[0]){
                swap(curBlock->childBlock[i], newChildBlock);
            }
        }
        curBlock->childBlock[i] = newChildBlock;

         for(i=0;curBlock->childBlock[i]!=NULL;i++){
            curBlock->childBlock[i]->parentBlock = curBlock;
        }
    }

}

void insert(Block *curBlock, int val){

    if(curBlock->childBlock[0]!=NULL)
    {
       for(int i=0; i<=curBlock->tNodes; i++)
       {
            if(val < curBlock->value[i])
            {   insert(curBlock->childBlock[i], val);
                if(curBlock->tNodes==numberOfPointers)
                    split(curBlock,false);
                break;
            }
       } 
    }
    else if(curBlock->childBlock[0]==NULL)
    {
        curBlock->tNodes++;
        for(int i=0; i<=curBlock->tNodes; i++)
       {
            if(val < curBlock->value[i])
            {   swap(curBlock->value[i], val);
                
            }
            
       } 
       if(curBlock->tNodes==numberOfPointers)
                split(curBlock,true);

    }

}

// void print(vector < Block* > Blocks){
//     vector < Block* > newBlocks;
//     for(int i=0; i<Blocks.size(); i++){ //for every block
//         Block *curBlock = Blocks[i];

//         cout <<"[|";
//         int j;
//         for(j=0; j<curBlock->tNodes; j++){  //traverse the childBlocks, print values and save all the childBlocks
//             cout << curBlock->value[j] << "|";
//             if(curBlock->childBlock[j]!=NULL)
//             newBlocks.push_back(curBlock->childBlock[j]);
//         }
//         if(curBlock->value[j]==INT_MAX && curBlock->childBlock[j]!=NULL)
//             newBlocks.push_back(curBlock->childBlock[j]);

//         cout << "]  ";
//     }

//     if(newBlocks.size()==0){ //if there is no childBlock block left to send out then just the end of the recursion

//         puts("");
//         puts("");
//         Blocks.clear();
//         //exit(0);
//     }
//     else {                    //else send the childBlocks to the recursion to continue to the more depth
//         puts("");
//         puts("");
//         Blocks.clear();
//         print(newBlocks);
//     }
// }

void find(Block *curBlock, int val)
{
    if(curBlock->childBlock[0]!=NULL)
    {
       for(int i=0; i<=curBlock->tNodes; i++)
       {
            if(val < curBlock->value[i])
               {find(curBlock->childBlock[i], val);
                return;
            }

            
       } 
    }
    else if(curBlock->childBlock[0]==NULL)
    {
        for(int i=0; i<=curBlock->tNodes; i++)
       {
            if(val == curBlock->value[i])
            {   
                cout<<"YES"<<endl;
                return;
            }
            
       } 
       
    }
    cout<<"NO"<<endl;

}

void range(Block *curBlock, int val1,int val2)
{
    if(curBlock->childBlock[0]!=NULL)
    {
       for(int i=0; i<=curBlock->tNodes; i++)
       {
            if(val1 <= curBlock->value[i])
               {range(curBlock->childBlock[i], val1,val2);
                return;}

            
       } 
    }
    else if(curBlock->childBlock[0]==NULL)
    {
        int count=0;
        while(1)
        {

        for(int i=0; i<=curBlock->tNodes; i++)
        {
            if(val1 <= curBlock->value[i]&&val2 >= curBlock->value[i])
            {   
                count++;
                // cout<<curBlock->value[i]<<" ";
            }
            else if(curBlock->value[i] > val2 )
            {
                break;
            }

            
        }
        if(curBlock->brotherBlock!=NULL)curBlock =  curBlock->brotherBlock;
        else break; 
        }
       cout<<count<<endl;
       
    }

}


int main(int argc, char const *argv[]){
    int n, B, M;
    string fileName;
    fileName=argv[1];

    // //M=(long long) (argv[2]); //No use of this in code

    B=atoi(argv[3]);

    numberOfPointers = (B - 1)/4;
    if(numberOfPointers < 3)
        numberOfPointers = 3;
    // cout<<numberOfPointers;
    // fileRead(n, file_name);
    // vector<int> num = {1,2,3,4,5};
    // vector<int> num = {1,4,7,10,17,21,31,25,19,20,28,42};
    // vector<int> num = {5,10,15,20,25,28,30,50,55,60,65,70,75,80,85,90,95};
    // vector<int> num = {5,10,15,20,20,20,20,20,20,25,28,30,50,55,60,65,70,75,80,85,90,95};
    // vector<int> num = {11,5,10,15,4,20,20,25,28,30,6,50,55,60,44,65,70,75,100,80,85,90,95,8,20};



    // printf("Pointers: ");
    // scanf("%d", &numberOfPointers);
    rootBlock = new Block();

    int value1, value2;
    string line;
    ifstream infile(fileName);
    while(getline(infile, line))
    {
        if(line.find("INSERT") != string::npos)
        {
            istringstream (line.substr(7)) >> value1;
            insert(rootBlock, value1);
        }
        else if(line.find("RANGE") != string::npos)
        {
            istringstream (line.substr(6)) >> value1 >> value2;
            range(rootBlock, value1, value2);
        }
        else if(line.find("FIND") != string::npos)
        {
            istringstream (line.substr(5)) >> value1;
            find(rootBlock,value1);
        }
        else if(line.find("COUNT") != string::npos)
        {
            istringstream (line.substr(6)) >> value1;
            range(rootBlock,value1,value1);
        }
        else
            cout << "Invalid Command : ";
    }

    // vector<Block*> Blocks;
    // Blocks.clear();
    // Blocks.push_back(rootBlock);
    // print(Blocks);
    // puts("");



    return 0;
}