{
    init: function(elevators, floors) {

        for(var i = 0;i < floors.length;i++){
            floors[i].on("up_button_pressed", function() {elevators[0].goToFloor(this.floorNum());} );
            floors[i].on("down_button_pressed", function() {elevators[1].goToFloor(this.floorNum());} );
        }
        
        for(var i = 0;i < 2;i++){
            elevators[i].on("floor_button_pressed", function(floorNum) {
                this.goToFloor(floorNum);
            });
        }
        
        // Whenever the elevator is idle (has no more queued destinations) ...
        elevators[0].on("idle", function() {
            this.goToFloor(0);
        });
        elevators[1].on("idle", function() {
            this.goToFloor(5);
        });
    },
    update: function(dt, elevators, floors) {
    }
}