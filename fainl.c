//
// Created by MATAN on 09/08/2023.
//מונה מתאפס ל100
//מקבל שורה עד הסוף
//מונה מקבל 1
//בודק האם המילה הראשונה תווית
//אם כן מכניס אותה לטבלת תוויות עם המונה
//אם התווית קיימת מוציא שגיאה
// ממשיך למילה השנייה
//אם המילה stop מקודד 15 ב12 סיביות
// אם המילה סטרינג מקודד אות אות בין הגרשיים
//מעלה את המונה בכל קידוד אות
//מוסיף קידוד של שורת אפס
//אם המילה דאטה מקודד את המספרים
//אם המילה הוראה  מקודד מילה ראשונה לפי כמה תנאים

#include "data.h"

resetMemoryCounters();


//פונקציה שעוברת על שורה שורה ומטפלת בה
while(getc){
    increaseInstructionCounter(1); //מעלה מונה ב1
    if (isLabel(char)){
        table (char, IC); // מכניס לטבלה ללא הנקודתיים עם מספר בפונקציה צריך לבדוק אם כבר קיים
    } //בודק תווית

    //בודק סטופ
    if(isStop(char)){
        addNode(&list, creatNode(data(15), IC, "stop"));
        increaseInstructionCounter(1); //מעלה מונה ב1
    }

    //בודק סטרינג
    if(isString(char)){
        kidodString(nextChar); //מקודד כל אות ללא הגרשיים ומוסיף 00000000 בסוף מעלה בכל קידוד את המונה
    }

    //בודק דאטה
    if(isData(char)){
        kidodData(nextChar); //מקודד את כל המספרים ללא הפסיקים ומעלה כל פעם את המונה
    }


}
