class SensorsController < ApplicationController
	before_filter :load_sensor_type

	# GET /sensors
	def index
		@sensors = Sensor.all
		
		respond_to do |format|
			format.html
		end 
	end
	
	def new
		@sensor = Sensor.new
		
		respond_to do |format|
			format.html 
		end 
	end
	
	def show
		@sensor = Sensor.find(params[:id])
		
		respond_to do |format|
			format.html 
		end 
	end 
	
	def edit
		@sensor = Sensor.find(params[:id])
	end
	
	#POST /sensors
	def create
		@sensor = Sensor.new(params[:sensor])
		
		respond_to do |format|
			if @sensor.save		
				format.html { redirect_to @sensor, :notice => 'Sensor erfolgreich erstellt' }
			else	
				format.html { render :action => "new" }
			end
		end 
	end 
		
	def update
		@sensor = Sensor.find(params[:id])
		
		respond_to do |format|
			if @sensor.update_attributes(params[:sensor])
				format.html { redirect_to @sensor, :notice => 'Änderungen erfolgreich gespeichert' }
			else
				format.html { render :action => "edit" }
			end
		end 
	end 
	
	def destroy
		@sensor = Sensor.find(params[:id])
		@sensor.destroy
		
		respond_to do |format|
			format.html { redirect_to(sensors_url) }
		end 
	end 
	
	private 
		def load_sensor_type
			@sensor_type = SensorType.find(params[:sensor_type_id])
		end 
			
end












