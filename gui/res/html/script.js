angular.module('opengov', ['nvd3'])
	
	.controller('dataCntl', function($scope, $http) {

        $scope.title = 'Budget Data';
        $scope.description = 'All data graphed';
        $scope.data = [];
        var objName = "";

        $http.get('../../../data.json').then( function ( response ) {
		    $scope.dataset = response.data;
            $scope.totalUniv = $scope.dataset.length;

			$scope.clearFilter = function() {
				$scope.query = '';
			};        

            $scope.fillData = function(){
                for(var i=0; i<$scope.dataset.length; i++){
                $scope.data[i] = {};
                    $scope.data[i].key = $scope.dataset[i].query;            
                    $scope.data[i].y =  $scope.dataset[i].amt.replace(/,/g,"");
                }
            };

            $scope.fillData();
        });

        $scope.options = {
            chart: {
                type: 'pieChart',
                height: 500,
                x: function(d){return d.key;},
                y: function(d){return d.y;},
                showLabels: false,
                duration: 500,
                labelThreshold: 0.01,
                labelSunbeamLayout: true,
                legend: {
                    margin: {
                        top: 5,
                        right: 35,
                        bottom: 5,
                        left: 0
                    }
                }
            }
        };
	});
