#include <vector>
#include <string>
#include <stdio.h>
#include <stack>
#include <iostream>

using namespace std;

class Variable 
{
  private:
    string variableName;
    bool instantiated;
    bool value;

  public:
    Variable(string symptom) {
      variableName = symptom;
      instantiated = false;
    }
    
    void setInstantiated(bool x, bool y) {
      instantiated = x;
      value = y;
    }

    bool getInstantiated() {
      return instantiated;
    }

    string getVariable() {
      return variableName;
    }
    
    bool getValue() {
      return value;
    }
};

class Knowledge
{
  private:
    int ruleNumber;
    vector<pair<string, bool>> condition;
    pair<string, string> conclusion;
    pair<string, bool> intermediate;

  public:
    Knowledge(int number) {
      ruleNumber = number;
      intermediate = make_pair("MENTAL DISORDER", true);
    }
    void setCondition(string name, bool answer) {
      condition.push_back(make_pair(name, answer));
    }
    void setConclusion(string disease, string answer) {
      conclusion = make_pair(disease, answer);      
    }
    void setIntermediate(string name, bool answer) {
      intermediate = make_pair(name, answer);
    }
    int getRuleNumber() {
      return ruleNumber;
    }
    vector<pair<string, bool>> getConditions() {
      return condition;
    }
    string getConclusion() {
      return conclusion.second;
    }
    string getConclusionType() {
      return intermediate.first;
    }
    string getIntermediateName() {
      return intermediate.first;
    }
    bool getIntermediate() {
      return intermediate.second;
    }
    
};

class Conclusion
{
  private:
    int ruleNumber;
    int clauseNumber;
  public:
    Conclusion(int x) {
      ruleNumber = x;
      clauseNumber = 1;
    }
    void increaseClauseNumber() {
      clauseNumber++;
    }
    int getRule() {
      return ruleNumber;
    }
    int getClause() {
      return clauseNumber;
    }
};

vector<pair<int, string>> setConclusionList()
{
  // set conclusion list
  vector<pair<int, string>> conclusionList;
  conclusionList.push_back(make_pair(10, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(20, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(30, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(40, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(50, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(60, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(70, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(80, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(90, "GROUP1"));
  conclusionList.push_back(make_pair(100, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(110, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(120, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(130, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(140, "GROUP2"));
  conclusionList.push_back(make_pair(150, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(160, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(170, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(180, "GROUP3"));
  conclusionList.push_back(make_pair(190, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(200, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(210, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(220, "MENTAL DISORDER"));
  conclusionList.push_back(make_pair(230, "MENTAL DISORDER"));

  return conclusionList;
}
  
vector<Variable> setVariableList() 
{
  // set variable list
  vector<Variable> variableList;
  variableList.push_back(Variable("sadness"));
  variableList.push_back(Variable("insomnia"));
  variableList.push_back(Variable("overeating"));
  variableList.push_back(Variable("gain weight"));
  variableList.push_back(Variable("hopelessness"));
  variableList.push_back(Variable("mood swing"));
  variableList.push_back(Variable("sweating"));
  variableList.push_back(Variable("tightness")); 
  variableList.push_back(Variable("overthinking"));
  variableList.push_back(Variable("passing out"));
  variableList.push_back(Variable("scared of closed space"));
  variableList.push_back(Variable("chest pain"));
  variableList.push_back(Variable("diziness"));
  variableList.push_back(Variable("repetitive movement"));
  variableList.push_back(Variable("inability to speak"));
  variableList.push_back(Variable("excited"));
  variableList.push_back(Variable("rapid eye movement"));
  variableList.push_back(Variable("learning disability"));
  variableList.push_back(Variable("confusion"));
  variableList.push_back(Variable("loss of memory"));
  variableList.push_back(Variable("poor judgement")); 
  variableList.push_back(Variable("low mood"));
  variableList.push_back(Variable("delusion"));
  variableList.push_back(Variable("suicidal"));
  variableList.push_back(Variable("fasting"));
  variableList.push_back(Variable("vomiting"));
  variableList.push_back(Variable("lack of social skills"));
  variableList.push_back(Variable("attraction to fire"));
  variableList.push_back(Variable("problem spelling"));
  variableList.push_back(Variable("scratching"));
  variableList.push_back(Variable("skin picking"));
  variableList.push_back(Variable("excessive sleep"));
  variableList.push_back(Variable("hallucination"));
  variableList.push_back(Variable("lying"));
  variableList.push_back(Variable("hearing voices"));
  variableList.push_back(Variable("feeling detached"));
  variableList.push_back(Variable("anxiety"));
  variableList.push_back(Variable("fainting"));

  return variableList;
}

void setClauseVariableList(string* list) 
{ 
  //Rule 10
  list[1] = "sadness";
  list[2] = "insomnia";
  list[3] = "overeating";
  list[4] = "gain weight";
  list[5] = "s";
  list[6] = "s";
  list[7] = "s";
  //Rule 20
  list[8] = "sadness";
  list[9] = "insomnia";
  list[10] = "overeating";
  list[11] = "hopelessness";
  list[12] = "s";
  list[13] = "s";
  list[14] = "s";
  //Rule 30
  list[15] = "sadness";
  list[16] = "insomnia";
  list[17] = "overeating";
  list[18] = "hoplessness";
  list[19] = "mood swing";
  list[20] = "s";
  list[21] = "s";
  //Rule 40
  list[22] = "sadness";
  list[23] = "sweating";
  list[24] = "tightness";
  list[25] = "overthinking";
  list[26] = "passing out";
  list[27] = "s";
  list[28] = "s";
  //Rule 50
  list[20] = "sadness";
  list[30] = "sweating";
  list[31] = "tightness";
  list[32] = "overthinking";
  list[33] = "scared of closed space";
  list[34] = "s";
  list[35] = "s";
  //Rule 6
  list[36] = "sadness";
  list[37] = "sweating";
  list[38] = "tightness";
  list[39] = "chest pain";
  list[40] = "dizziness";
  list[41] = "s";
  list[42] = "s";
  //Rule 70
  list[43] = "sadness";
  list[44] = "sweating";
  list[45] = "repetitive movement";
  list[46] = "inability to speak";
  list[47] = "excited";
  list[48] = "s";
  list[49] = "s";
  //Rule 80
  list[50] = "sadness";
  list[51] = "sweating";
  list[52] = "repetitive movement";
  list[53] = "inability to speak";
  list[54] = "excited";
  list[55] = "rapid eye movement";
  list[56] = "s";
  //Rule 90
  list[57] = "sadness";
  list[58] = "sweating";
  list[59] = "repetitive movement";
  list[60] = "s";
  list[61] = "s";
  list[62] = "s";
  list[63] = "s";
  //Rule 100
  list[64] = "sadness";
  list[65] = "sweating";
  list[66] = "repetitive movement";
  list[67] = "inability to speak";
  list[68] = "learning disability";
  list[69] = "s";
  list[70] = "s";
  //Rule 110
  list[71] = "GROUP1";
  list[72] = "confusion";
  list[73] = "loss of memory";
  list[74] = "poor judgement";
  list[75] = "s";
  list[76] = "s";
  list[77] = "s";
  //Rule 120
  list[78] = "GROUP1";
  list[79] = "confusion";
  list[80] = "loss of memory";
  list[81] = "poor judgement";
  list[82] = "s";
  list[83] = "s";
  list[84] = "s";
  //Rule 130
  list[85] = "GROUP1";
  list[86] = "confusion";
  list[87] = "low mood";
  list[88] = "delusion";
  list[89] = "suicidal";
  list[90] = "s";
  list[91] = "s";
  //Rule 140
  list[92] = "GROUP1";
  list[93] = "confusion";
  list[94] = "low mood";
  list[95] = "delusion";
  list[96] = "suicidal";
  list[97] = "s";
  list[98] = "s";
  //Rule 150
  list[99] = "GROUP1";
  list[100] = "confusion";
  list[101] = "low mood";
  list[102] = "s";
  list[103] = "s";
  list[104] = "s";
  list[105] = "s";
  // Rule 160
  list[106] = "GROUP2";
  list[107] = "fasting";
  list[108] = "vomiting";
  list[109] = "s";
  list[110] = "s";
  list[111] = "s";
  list[112] = "s";
  //Rule 170
  list[113] = "GROUP2";
  list[114] = "fasting";
  list[115] = "lack of social skills";
  list[116] = "attraction to fire";
  list[117] = "s";
  list[118] = "s";
  list[119] = "s";
  //Rule 180
  list[120] = "GROUP2";
  list[121] = "fasting";
  list[122] = "lack of social skills";
  list[123] = "attraaction to fire";
  list[124] = "problem spelling";
  list[125] = "s";
  list[126] = "s";
  //Rule 190
  list[127] = "GROUP2";
  list[128] = "fasting";
  list[129] = "lack of social skills";
  list[130] = "s";
  list[131] = "s";
  list[132] = "s";
  list[133] = "s";
  //Rule 200
  list[134] = "GROUP3";
  list[135] = "scratching";
  list[136] = "skin picking";
  list[137] = "s";
  list[138] = "s";
  list[139] = "s";
  list[140] = "s";
  //Rule 210
  list[141] = "GROUP3";
  list[142] = "scratching";
  list[143] = "excessive sleep";
  list[144] = "hallucination";
  list[145] = "s";
  list[146] = "s";
  list[147] = "s";
  list[148] = "s";
  //Rule 220
  list[149] = "GROUP3";
  list[150] = "scratching";
  list[151] = "excessive sleep";
  list[152] = "lying";
  list[153] = "hearing voices";
  list[154] = "feeling detached";
  list[155] = "s";
  // Rule 230
  list[156] = "GROUP3";
  list[157] = "excessive sleep";
  list[158] = "lying";
  list[159] = "loss of memory";
  list[160] = "anxiety";
  list[161] = "fainting";
  list[162] = "s";
}

vector<Knowledge> setKnowledgeBase() {
  //set rules
  vector<Knowledge> rules;
  //rule 10
  rules.push_back(Knowledge(10));
  rules[0].setCondition("sadness", true);
  rules[0].setCondition("insomnia", true);
  rules[0].setCondition("overeating", false);
  rules[0].setCondition("gain weight", true);
  rules[0].setConclusion("MENTAL DISORDER", "Major Depressive Disorder");
  //rule 20 
  rules.push_back(Knowledge(20));
  rules[1].setCondition("sadness", true);
  rules[1].setCondition("insomnia", true);
  rules[1].setCondition("overeating", true);
  rules[1].setCondition("hopelessness", true);
  rules[1].setConclusion("MENTAL DISORDER", "Dysthymia");
  //rule 30
  rules.push_back(Knowledge(30));
  rules[2].setCondition("sadness", true);
  rules[2].setCondition("insomnia", true);
  rules[2].setCondition("overeating", true);
  rules[2].setCondition("hopelessness", false);
  rules[2].setCondition("mood swing", true);
  rules[2].setConclusion("MENTAL DISORDER", "Bipolar Disorder");
  //rule 40
  rules.push_back(Knowledge(40));
  rules[3].setCondition("sadness", false);
  rules[3].setCondition("sweating", true);
  rules[3].setCondition("tightness", true);
  rules[3].setCondition("overthinking", true);
  rules[3].setCondition("passing out", true);
  rules[3].setConclusion("MENTAL DISORDER", "Generalized Anxiety Disorder");
  //rule 50
  rules.push_back(Knowledge(50));
  rules[4].setCondition("sadness", false);
  rules[4].setCondition("sweating", true);
  rules[4].setCondition("tightness", true);
  rules[4].setCondition("overthinking", false);
  rules[4].setCondition("scared of closed space", true);
  rules[4].setConclusion("MENTAL DISORDER", "Claustrophobia");
  //rule 60
  rules.push_back(Knowledge(60));
  rules[5].setCondition("sadness", false);
  rules[5].setCondition("sweating", true);
  rules[5].setCondition("tightness", false);
  rules[5].setCondition("chest pain", true);
  rules[5].setCondition("diziness", true);
  rules[5].setConclusion("MENTAL DISORDER", "Panic Disorder with Agrophobia");
  //rule 70
  rules.push_back(Knowledge(70));
  rules[6].setCondition("sadness", false);
  rules[6].setCondition("sweating", false);
  rules[6].setCondition("repetitive movement", true);
  rules[6].setCondition("inability to speak", true);
  rules[6].setCondition("excited", true);
  rules[6].setConclusion("MENTAL DISORDER", "Cataonia");
  //rule 80
  rules.push_back(Knowledge(80));
  rules[7].setCondition("sadness", false);
  rules[7].setCondition("sweating", false);
  rules[7].setCondition("repetitive movement", true);
  rules[7].setCondition("inability to speak", true);
  rules[7].setCondition("excited", false);
  rules[7].setCondition("rapid eye movement", true);
  rules[7].setConclusion("MENTAL DISORDER", "Stuttering");
  //rule 90
  rules.push_back(Knowledge(90));
  rules[8].setCondition("sadness", false);
  rules[8].setCondition("sweating", false);
  rules[8].setCondition("repetitive movement", false);
  rules[8].setIntermediate("GROUP1", true);
  //rule 100
  rules.push_back(Knowledge(100));
  rules[9].setCondition("sadness", false);
  rules[9].setCondition("sweating", false);
  rules[9].setCondition("repetitive movement", true);
  rules[9].setCondition("inability to speak", false);
  rules[9].setCondition("learning disability", true);
  rules[9].setConclusion("MENTAL DISORDER", "Autism");
  //rule 110
  rules.push_back(Knowledge(110));
  rules[10].setCondition("GROUP1", true);
  rules[10].setCondition("confusion", true);
  rules[10].setCondition("loss of memory", true);
  rules[10].setCondition("poor judgement", true);
  rules[10].setConclusion("MENTAL DISORDER", "Alzheimer's Disease");
  //rule 120
  rules.push_back(Knowledge(120));
  rules[11].setCondition("GROUP1", true);
  rules[11].setCondition("confusion", true);
  rules[11].setCondition("loss of memory", true);
  rules[11].setCondition("poor judgement", false);
  rules[11].setConclusion("MENTAL DISORDER", "Amnestic Disorder");
  //rule 130
  rules.push_back(Knowledge(130));
  rules[12].setCondition("GROUP1", true);
  rules[12].setCondition("confusion", false);
  rules[12].setCondition("low mood", true);
  rules[12].setCondition("delusion", true);
  rules[12].setCondition("suicidal", true);
  rules[12].setConclusion("MENTAL DISORDER", "Schizo_Affective Disorder");
  //rule 140
  rules.push_back(Knowledge(140));
  rules[13].setCondition("GROUP1", true);
  rules[13].setCondition("confusion", true);
  rules[13].setCondition("low mood", true);
  rules[13].setCondition("delusion", true);
  rules[13].setCondition("suicidal", false);
  rules[13].setConclusion("MENTAL DISORDER", "Schizophrenia");
  //rule 150
  rules.push_back(Knowledge(150));
  rules[14].setCondition("GROUP1", true);
  rules[14].setCondition("confusion", false);
  rules[14].setCondition("low mood", false);
  rules[14].setIntermediate("GROUP2", true);
  //rule 160
  rules.push_back(Knowledge(160));
  rules[15].setCondition("GROUP2", true);
  rules[15].setCondition("fasting", true);
  rules[15].setCondition("vomiting", true);
  rules[15].setConclusion("MENTAL DISORDER", "Bulimia");
  //rule 170
  rules.push_back(Knowledge(170));
  rules[16].setCondition("GROUP2", true);
  rules[16].setCondition("fasting", false);
  rules[16].setCondition("lack of social skills", true);
  rules[16].setCondition("attraction to fire", true);
  rules[16].setConclusion("MENTAL DISORDER", "Pyromania");
  //rule 180
  rules.push_back(Knowledge(180));
  rules[17].setCondition("GROUP2", true);
  rules[17].setCondition("fasting", false);
  rules[17].setCondition("lack of social skills", true);
  rules[17].setCondition("attraction to fire", false);
  rules[17].setCondition("problem spelling", true);
  rules[17].setConclusion("MENTAL DISORDER", "Dyslexia");
  //rule 190
  rules.push_back(Knowledge(190));
  rules[18].setCondition("GROUP2", true);
  rules[18].setCondition("fasting", false);
  rules[18].setCondition("lack of social skills", false);
  rules[18].setIntermediate("GROUP3", true);
  //rule 200
  rules.push_back(Knowledge(200));
  rules[19].setCondition("GROUP3", true);
  rules[19].setCondition("scratching", true);
  rules[19].setCondition("skin picking", true);
  rules[19].setConclusion("MENTAL DISORDER", "Dermatillomania");
  //rule 210
  rules.push_back(Knowledge(210));
  rules[20].setCondition("GROUP3", true);
  rules[20].setCondition("scratching", false);
  rules[20].setCondition("excessive sleep", true);
  rules[20].setCondition("hallucination", true);
  rules[20].setConclusion("MENTAL DISORDER", "Narcolepsy");
  //rule 220
  rules.push_back(Knowledge(220));
  rules[21].setCondition("GROUP3", true);
  rules[21].setCondition("scratching", false);
  rules[21].setCondition("excessive sleep", false);
  rules[21].setCondition("lying", true);
  rules[21].setCondition("hearing voices", true);
  rules[21].setCondition("feeling detached", true);
  rules[21].setConclusion("MENTAL DISORDER", "Dissociative Identitiy Disorder");
  //rule 230
  rules.push_back(Knowledge(10));
  rules[22].setCondition("GROUP3", true);
  rules[22].setCondition("excessive sleep", false);
  rules[22].setCondition("lying", false);
  rules[22].setCondition("loss of memory", false);
  rules[22].setCondition("anxiety", true);
  rules[22].setCondition("fainting", true);
  rules[22].setConclusion("MENTAL DISORDER", "Epilepsy");
  return rules;
}

int convert(int rule) {
  int number = 7 * (rule / 10 - 1) + 1;
  return number;
}

void askQuestion(vector<Variable> &variableList, int i) {
  cout<<"Do you have '"+ variableList[i].getVariable() + "'? (YES/NO)\n";
  string yesno;
  cin>>yesno;

  if (yesno == "YES") variableList[i].setInstantiated(true, true);
  else variableList[i].setInstantiated(true, false);
}

string Backwardchaining() 
{
  // set initial needed lists
  //conclusion list
  vector<pair<int, string>> conclusionList = setConclusionList();
  //variable list
  vector<Variable>variableList = setVariableList();
  //clause variable list
  string clauseVariableList[163];
  fill(clauseVariableList, clauseVariableList + 163, " ");
  setClauseVariableList(clauseVariableList);
  //create Knowledge Base
  vector<Knowledge> knowledgeBase = setKnowledgeBase();
  string MentalDisorder = "not available";
  
  // init conclusion stack
  stack<Conclusion> conclusionStack;
  int ruleNum = 10;
  conclusionStack.push(Conclusion(ruleNum));
  bool notsame = false;
  bool intermediate = false;
  //look through conclusion list
  for (int k = 0; k < knowledgeBase.size(); k++) {
    notsame = false;
    //intermediate result
    Knowledge currentRule = knowledgeBase[k];
    if (currentRule.getConclusionType() != "MENTAL DISORDER") {
      variableList.push_back(Variable(knowledgeBase[k].getIntermediateName()));
      variableList[variableList.size() -1].setInstantiated(true, true);
      ruleNum += 10;
      conclusionStack.push(Conclusion(ruleNum));
      continue;
    }
    
    Conclusion lookup = conclusionStack.top();
    // go through the conditions of the found rule from knowledge base
    int clause = convert(lookup.getRule());
    vector<pair<string, bool>> condition = currentRule.getConditions();
    for (int i = 0; i < condition.size(); i++) {
      int index;
      // find match from variable list
      for (int j = 0; j < variableList.size(); j++) { 
        if (clauseVariableList[clause] == variableList[j].getVariable()) {
          index = j;
          break;
        }
      }
      // if not instantiated, ask user
      if (variableList[index].getInstantiated() == false) {
        askQuestion(variableList, index);
      }
      int where; 
      for (int j = 0; j < condition.size(); j++) {
        if (condition[j].first == variableList[index].getVariable()) {
          where = j;
          break;
        }
      }
      if(variableList[index].getValue() == condition[where].second) {
        lookup.increaseClauseNumber();
        clause++;
      } else notsame = true;
      if (notsame) break;
      
    }
    if (notsame == true) {
      conclusionStack.pop();
      ruleNum += 10;
      conclusionStack.push(Conclusion(ruleNum));
    }
    else if (notsame == false) {
      MentalDisorder = currentRule.getConclusion();
      break;
    }
  }

  cout<<"YOUR mental disorder is: " + MentalDisorder;

  return MentalDisorder;
}
