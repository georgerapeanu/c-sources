{


    init: function(elevators, floors) {

        var cnt = floors.length;

        console.log("pula");
        console.clear();

        var goingUp = [];
        var goingDown = [];
        var mode = [];

        for(var i = 0;i < elevators.length;i++){
            mode.push(0);
            elevators[i].goToFloor(0);
        }

        for(var i = 0;i < floors.length;i++){
            floors[i].on("up_button_pressed", function() {goingUp.push(this.floorNum());} );
            floors[i].on("down_button_pressed", function() {goingDown.push(this.floorNum());} );
        }

        for(var x = 0;x < elevators.length;x++){
            (function(x){
                elevators[x].on("idle", function() {
                    console.log("pressed");
                    console.log(this.getPressedFloors());
                    console.log(this.loadFactor() == elevators[x].loadFactor());
                    console.log(x);
                    console.log(mode);
                    console.log(mode[x]);
                    if(mode[x] == 0){
                        mode[x] = 1 - mode[x];
                        goingUp = [...new Set(goingUp)].sort();
                        goingDown = [...new Set(goingDown)].sort();
                        goingDown.reverse();
                        console.log(goingUp);
                        console.log(goingUp.length);
                        console.log(goingDown);
                        console.log(goingDown.length);
                        if(goingUp.length > goingDown.length){
                            this.goingDownIndicator(true);
                            this.goingUpIndicator(true);
                            for(var i = 0;i < this.maxPassengerCount() && i < goingUp.length;i++){
                                this.goToFloor(goingUp[0]);
                                goingUp.shift();   
                            }
                        }
                        else if(goingDown.length > 0){
                            this.goingDownIndicator(true);
                            this.goingUpIndicator(true);
                            for(var i = 0;i < this.maxPassengerCount() && i < goingDown.length;i++){
                                this.goToFloor(goingDown[0]);
                                goingDown.shift();   
                            }
                        }
                        else{
                            this.goToFloor(this.currentFloor());
                            mode[x] = 0;
                        }
                    }
                    else{
                        console.log("going places");
                        console.log(x);
                        mode[x] = 1 - mode[x];
                        var tmp = this.getPressedFloors().sort();
                        if(this.currentFloor() - tmp[0] > tmp[tmp.length - 1] - this.currentFloor()){
                            tmp = tmp.reverse();
                        }
                        console.log(this.getPressedFloors());
                        console.log(tmp);
                        for(var i = 0;i < tmp.length;i++){
                            this.goToFloor(tmp[i]);   
                        }
                    }
                });})(x);    
        }

    },
        update: function(dt, elevators, floors) {
        }
}