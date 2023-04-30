#include <iostream>
#include "file_manager.h"
#include "FCompress.h"
int main()
{
    file_manager fm;
    /*fm.writeData("test.txt", 
        "The Benefits of Regular Exercise\n"
        "Regular exercise is an essential component of a healthy lifestyle.Studies have shown that people who engage in regular physical activity are less likely to develop chronic diseases such as obesity, heart disease, and diabetes.In addition to its health benefits, exercise can also improve your mood, boost your energy levels, and help you sleep better at night.\n"
        "One of the main benefits of regular exercise is its ability to help control weight.Physical activity burns calories, helping you to maintain a healthy weight or lose excess body fat.Exercise also increases muscle mass, which further promotes weight loss by boosting your metabolism.\n"
        "Regular exercise can also help reduce your risk of developing heart disease.Cardiovascular exercise, such as running or cycling, strengthens the heartand improves circulation.This can reduce your risk of high blood pressure, stroke, and other cardiovascular diseases.\n"
        "In addition to its physical benefits, exercise can also improve your mental health.Exercise has been shown to reduce symptoms of anxietyand depression, and can even help prevent these conditions from developing in the first place.This is because exercise releases endorphins, which are natural chemicals that promote feelings of happinessand well - being.\n"
        "Finally, regular exercise can also improve your sleep quality.Studies have shown that people who engage in regular physical activity tend to fall asleep fasterand enjoy more restful sleep compared to those who are sedentary.This is because exercise helps to regulate your circadian rhythm, which is the body’s internal clock that regulates sleepand wake cycles.\n"
        "In conclusion, regular exercise is essential for maintaining good healthand well - being.It can help you control your weight, reduce your risk of chronic diseases, improve your mental health, and promote better sleep.So next time you’re feeling sluggish, take a walk or hit the gym – your body will thank you!");
    */
    fm.writeData("test.txt", "hello123451234\n111\n222");
    FCompress FC1("test.txt");
    FC1.process();

    FCompress FC2("test.hfm");
    FC2.process();
}
