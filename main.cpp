#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include "avl.h"
using namespace std;
using namespace std::chrono;
//This function receives the ehead of linked which is present on the node of AVL tree as if there
//is a collision of souce airports so that appropriate destination can be found in the list with 
//its price
void print_list(LLNode *head){
    if(head==NULL){
        return;
    }
    else{
        LLNode* temp = head;
        while(temp!=NULL){
            cout<<"Destination: "<<temp->destination<<" Price: $"<<temp->price<<" Date: "<<temp->date<<endl;
            temp = temp->next;
        }
    }
}

//This function is is sorting the linked list according to the price so that minimum can be found
void sort_list(LLNode* head){
    if(head==NULL){
        return;
    }
    else{
        int temp_price,iter_price;
        LLNode *temp = head;
        while(temp->next!=NULL){
           
           //linked list iterator only for that node of AVL where source matches
            LLNode* iterator = temp->next;
            while(iterator!=NULL){
                temp_price = stoi(temp->price);
                iter_price = stoi(iterator->price);
                if(temp_price > iter_price){
                    swap(temp->price,iterator->price);
                    swap(temp->destination,iterator->destination);
                    swap(temp->date,iterator->date);
                }
                iterator = iterator->next;
            }
            temp = temp->next;
        }
    }
}
LLNode* find_cheapest(LLNode* head,string dest){
    LLNode* temp = head;
    while(temp!=NULL){
        if(temp->destination==dest){
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}
//inserting all of the source airports in the AVL Tree for Fast searching
void insert_in_tree(AVLTree &tree){
    fstream obj;
    obj.open("Data_2_okay.csv",ios::in);
    if (!obj.is_open()){
        cout<<"file not opened"<<endl;
        return;
    }
    auto start = high_resolution_clock::now();
    string orig,destt,date,pri;
    while (!obj.eof())
    {
        getline(obj,orig,',');
        getline(obj,destt,',');
        getline(obj,date,',');
        getline(obj,pri,'\n');

        //this check means that if any of the row in our file does not contain any of the column
        //whether source , destination or date . it is not pushing that as a node in the Tree
        if (orig!="" && destt!="" && date!=""){

            //saving destination ,price and date in linked list
            LLNode *temp2 = new LLNode(destt,pri,date);

            //saving that linked list and origin in AVL
            tree.root = tree.insert_tree(tree.root,orig,temp2);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout <<"Time taken in creating AVL is: "<<duration.count()<<" seconds"<<endl;
    system("PAUSE");

}
void display(){
    system("CLS");
    cout<<"------------Airline Route Checker-------------"<<endl<<endl;
    cout<<"Here is the List of Availale Sources to take-off :"<<endl;
    cout<<"--------------------------------------------------"<<endl<<endl;

    //some of the airports we have taken 
    cout<<" 1.VAJJ->Mumbai,India\t\t\t 2.OTHH->Doha,Qatar\t\t\t 3.YSSY->Sydney,Austrailia\n 4.PANC->Anchorage,USA\t\t\t 5.VIDP->Dehli,India\t\t\t 6.OMBD->Dubai,UAE\n 7.KJFK->Queen's USA\t\t\t 8.KSFO->California\t\t\t 9.RJTT->Tokyo,Japan\n10.EGLL->LongFord ,UK\t\t\t11.NZAA->AuckLand,NewZealand\t\t12.EHAM->Schiphol,Netherland\n13.LEMD->Madrid,Spain\t\t\t14.RKSI->Incheon,South Korea\t\t15.OLBA->Beirut,Lebnon\n16.OERK->Riyadh , Saudia Arabia\t\t17.KONT->Ontario,USA\t\t\t18.WIDD->Kepulauan Riau , Indonesia\n19.RCTP->Taiwan,China\t\t\t20.VABB->Mumbai,India\t\t\t21.KLDJ->Linden,USA\n22.VTBS->Thailand\t\t\t23.EDDF->Frankfurt,Germany\t\t24.RJBB->Kansai,Japan\n25.MMMX->Mexico\t\t\t\t26.LIMC->Provine of Varese,Itlay \t27.71KY->Peter's Burg,USA\n28.RPLL->Metro Manila,Phillppines\t29.YPAD->Adelaide,Austrailia\t\t30.OMDB->Dubai,UAE->\n31.LEBL->Barceolona,Spain\t\t32.LPAR->Portugal\t\t\t33.LSGG->SwitzerLand\n34.EKCH->kastrup,Denmark\t\t35.EINN->Clare,Ireland\t\t\t36.KDFW->DFW Airport , USA\n37.LKKL->Czechia\t\t\t38.WMKK->Selangor,Malaysia\t\t39.LILG->Itlay\n40.EPWA->Warszawa,Poland\t\t41.WSAC->Changai Airbase,Singapur \t42.WSSS->Changai Sinagapur Airport\n43.OMDW->Dubai,UAE\t\t\t44.LOWW->Schwechat,Austria\t\t45.KIAH->Huiston,USA\n-KTPA->Tempa ,USA\t\t\t46.FAOR->Johannesburg,South Africa \t47.TXKF->st.George's Bermuda\n48.KLAX->Los Angelas,California\t\t49.ZGSZ->Guangdong Provine,China\t50.VHHH->Chek lapKok,Honk-kong\n51.YMML->Melbourne,Austrailia\t\t52.LFPG->Roissy-en-France,France\t53.EGKK->Gatwick,UK\n54.UUEE->Moscow,Russia\t\t\t55.OERK->Riyadh , Saudia Arabia\n56.KONT->Ontario,USA\t\t\t57.WIDD->Kepulauan Riau , Indonesia\n";
    cout<<endl<<endl;
}
int get_choice()
{
    cout<<"Press 0 to exit"<<endl<<"Press 1 if you want to know only the minimum cost destination"<<endl<<"Press 2 if you want to know all the destinations of the given source"<<endl<<"Press 3 if you want to know the cheapest route avaialable to your destination"<<endl;
    int n;
    cin>>n;
    return n;
}
int main()
{
    AVLTree tree;
    //root of tree created
    insert_in_tree(tree);
    display();
    string source , destination;

    //any of from above or file
    cout<<"Enter the name equivalent to the Airport code , you want to take-off : ";
    getline(cin,source);
    if(!tree.is_present(tree.root,source)){
        //check if present or not the airport 
        cout<<"The given origin is not present in the data"<<endl;
        return 0;
    }
    auto start = high_resolution_clock::now();
    LLNode* temp_ll = tree.search_list(tree.root,source);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout <<"Time taken in searching is: "<<duration.count()<<" milliseconds"<<endl;
    system("PAUSE");
    start = high_resolution_clock::now();
    sort_list(temp_ll);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout <<"Time taken in sorting is: "<<duration.count()<<" milliseconds"<<endl;
    system("PAUSE");
    int choice;
    do{
            choice = get_choice();
            if(choice==1){
                cout<<"Origin is: "<<source<<" Destination is: "<<temp_ll->destination<<" Price is: $"<<temp_ll->price<<" Date is: "<<temp_ll->date<<endl;
            }
            else if(choice==2){
                cout<<"Origin is: "<<source<<endl;
                print_list(temp_ll);
            }
            else if(choice==3){
                //string dest;
                cout<<"Enter destination"<<endl;
                fflush(stdin);
                getline(cin,destination);
                LLNode* temp = find_cheapest(temp_ll,destination);
                if(temp!=NULL){
                    cout<<"Cheapest route found"<<endl;
                    cout<<"Destination is: "<<temp->destination<<" Date is: "<<temp->date<<" Price is: $"<<temp->price<<endl;
                }
            }
    }while(choice!=0);
    
    return 0;
}
