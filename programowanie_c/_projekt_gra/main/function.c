int potega(int podstawa,int potega){
    int spotengowana = podstawa;
    if(potega == 0){
        return 1;
    }
    for(int i = 0;i < potega;i++){
        spotengowana *= podstawa;
    }
    return spotengowana;

}