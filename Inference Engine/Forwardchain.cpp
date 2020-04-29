#include <vector>
#include <string.h>
#include <stdio.h>
#include <tuple>
#include <stack>
#include <iostream> 
#include <queue>
using namespace std;

class forwardKnowledge 
{
  private: 
    int ruleNum;
    string variable;
    string mentalDisorder;
    string treatment;
  public:
    forwardKnowledge(int num, string disorder) {
      ruleNum = num;
      variable = "MENTAL DISORDER";
      mentalDisorder = disorder;
    }
    void setTreatment(string how) {
      treatment = how;
    }
    int getruleNum() {
      return ruleNum;
    }
    string getmentalDisorder() {
      return mentalDisorder;
    }
    string getTreatment() {
      return treatment;
    }
};
// Clause Variable List for Forward Chaining
void forwardsetClauseVariableList(string* list) 
{
  list[1] = "MENTAL DISORDER";
  list[3] = "MENTAL DISORDER";
  list[5] = "MENTAL DISORDER";
  list[7] = "MENTAL DISORDER";
  list[9] = "MENTAL DISORDER";
  list[11] = "MENTAL DISORDER";
  list[13] = "MENTAL DISORDER";
  list[15] = "MENTAL DISORDER";
  list[17] = "MENTAL DISORDER";
  list[19] = "MENTAL DISORDER";
  list[21] = "MENTAL DISORDER";
  list[23] = "MENTAL DISORDER";
  list[25] = "MENTAL DISORDER";
  list[27] = "MENTAL DISORDER";
  list[29] = "MENTAL DISORDER";
  list[31] = "MENTAL DISORDER";
  list[33] = "MENTAL DISORDER";
  list[35] = "MENTAL DISORDER";
  list[37] = "MENTAL DISORDER";
  list[39] = "MENTAL DISORDER";

}
// Knowledge Base for Forward Chaining    
vector<forwardKnowledge> setforwardKnowledgeBase ()
{
  //set rules
  vector<forwardKnowledge> rules;
  
  //rule 10
  rules.push_back(forwardKnowledge(10, "Major Depressive Disorder"));
  rules[0].setTreatment("medications and psychotherapy and lifestyle changes");
  //rule 20
  rules.push_back(forwardKnowledge(20, "Dysthymia"));
  rules[1].setTreatment("medications and talk therapy");
  //rule30
  rules.push_back(forwardKnowledge(30, "Bipolar Disorder"));
  rules[2].setTreatment("medications and psychological counseling andpsychotherapy");
  //rule40
  rules.push_back(forwardKnowledge(40, "Generalized Anxiety Disorder"));
  rules[3].setTreatment("medications AND psychosocial therapy");  
  //rule50
  rules.push_back(forwardKnowledge(50, "Claustrophobia"));
  rules[4].setTreatment("CBT and Drug therapy and calming oils and visualization exercises"); 
  //rule60
  rules.push_back(forwardKnowledge(60, "Panic Disorder with Agrophobia"));
  rules[5].setTreatment("medications and Cognitive behavioral therapy"); 
  //rule70
  rules.push_back(forwardKnowledge(70, "Cataonia"));
  rules[6].setTreatment("medications and electroconvulsive therapy"); 
  //rule80
  rules.push_back(forwardKnowledge(80, "Stuttering"));
  rules[7].setTreatment("speech therapy and Electronic devices to enhance fluency and Cognitive behavioral therapy");
  //rule90
  rules.push_back(forwardKnowledge(90, "Autism"));
  rules[8].setTreatment("medications and psychosocial therapy");
  //rule100
  rules.push_back(forwardKnowledge(100, "Alzheimer's Disease"));
  rules[9].setTreatment("no cure, but take memantine and NMDA to slow down the process");
  //rule110
  rules.push_back(forwardKnowledge(110, "Amnestic Disorder"));
  rules[10].setTreatment("medications and psychosocial therapy");
  //rule120
  rules.push_back(forwardKnowledge(120, "Schizo_Affective Disorder"));
  rules[11].setTreatment("medications and psychosocial therapy and life skill training"); 
  //rule130
  rules.push_back(forwardKnowledge(130, "Schizophrenia"));
  rules[12].setTreatment("medications and psychological counseling and self-help resources");
  //rule140
  rules.push_back(forwardKnowledge(140, "Bulimia"));
  rules[13].setTreatment("psychotherapy and antidepressants");
  //rule150
  rules.push_back(forwardKnowledge(150, "Pyromania"));
  rules[14].setTreatment("Cognitive Behavioral Therapy and Aversion Therapy and Medications");
  //rule160
  rules.push_back(forwardKnowledge(160, "Dyslexia"));
  rules[15].setTreatment("lifelong problem AND specific educational approaches and techniques");
  //rule170
  rules.push_back(forwardKnowledge(170, "Dermatillomania"));
  rules[16].setTreatment("cognitive behavioral therapy and acceptance and commitment therapy and medications");
  //rule180
  rules.push_back(forwardKnowledge(180, "Narcolepsy"));
  rules[17].setTreatment("amphetamine-like stimulants and antidepressant drugs and Clomipramine");
  //rule190
  rules.push_back(forwardKnowledge(190, "Dissociative Identitiy Disorder"));
  rules[18].setTreatment("medications and psychotherapy and eye movement desensitization and reprocessing");
  //rule200
  rules.push_back(forwardKnowledge(200, "Epilepsy"));
  rules[19].setTreatment("anti-epileptic drugs like sodium valproate and carbamazepine");
  return rules;
}

int calculateRuleNumber(int clauseNum) 
{
  int ruleNum = ((clauseNum / 2) + 1) * 10;
  return ruleNum;
}

void Forwardchaining (string type, string disorder) 
{ 
  string treatment;
  //If we did not find a disorder in our database
  if(disorder == "not available") {
    cout<< "Sorry, our database does not recognize your symptoms\n";
    return;
  }

  //make Knowledge Base for Forward Chaining
  vector<forwardKnowledge> KnowledgeBase = setforwardKnowledgeBase();
  //make Clause Variable List for ForwardChaining
  int ClauseVariableListSize = 41;
  string ClauseVariableList[41];
  fill(ClauseVariableList, ClauseVariableList + 41, "s");
  forwardsetClauseVariableList(ClauseVariableList);
  //set conclusion variable queue
  queue<string> conclusionVariable;  
  //set variable List
  vector<tuple<string, bool, string>> variableList;
  //Instantiate Mental disorder with result from Backwardchaining
  variableList.push_back(make_tuple(type, true, disorder));
  //set clause variable pointer
  pair<int, int> clauseVariablePointer;
  //put variable into conclusion variable queue
  conclusionVariable.push(type);

  //go through clause variable list and find variable
  for (int i = 0; i < ClauseVariableListSize; i++) {
    if (ClauseVariableList[i] == conclusionVariable.front()) {
      //if found, put put it in the find the rule number
      int ruleNum = calculateRuleNumber(i);
      //update clause variable pointer
      clauseVariablePointer = make_pair(ruleNum, i);
    } else continue;
    int index;
    
    //go through knowledge base number to find correct rule
    for (int j = 0; j < KnowledgeBase.size(); j++) {
      if (KnowledgeBase[j].getruleNum() == clauseVariablePointer.first) {
          index = j;
          break;
      }
    }
    forwardKnowledge currentRule = KnowledgeBase[index];
    //does the rule match our disorder?
    if (currentRule.getmentalDisorder() == get<2>(variableList[0])) {
      //yes, set treatment and exit the loop
      treatment = currentRule.getTreatment();
      break;
    }
    //no, continue searching clause variable list
  }
     
  cout<<"Your treatment is: " + treatment;
  
}
