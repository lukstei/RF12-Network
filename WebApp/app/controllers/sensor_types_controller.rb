class SensorTypesController < ApplicationController
	
	def index
		@sensor_types = SensorType.all
		
		respond_to do |format|
			format.html
		end 
	end 
	
	def new
		@sensor_type = SensorType.new
		
		respond_to do |format|
			format.html
		end 
	end
	
	def show
		@sensor_type = SensorType.find(params[:id])
		
		respond_to do |format|
			format.html
		end 
	end 
	
	def edit
		@sensor_type = SensorType.find(params[:id])
	end 
	
	def create
		@sensor_type = SensorType.create(params[:sensor_type])
		
		respond_to do |format|
			if  @sensor_type.save
				format.html { redirect_to @sensor_type, :notice => 'Sensor Typ erfolgreich erstellt' }
			else
				format.html { render :action => "new" }
			end 
		end 
	end 
	
	def update
		@sensor_type = SensorType.find(params[:id])
		
		respond_to do |format|
			if @sensor_type.update_attributes(params[:sensor_type])
				format.html { redirect_to @sensor_type, :notice => 'Änderungen erfolgreich gespeichert' }
			else 
				format.html { render :action => "edit" }
			end 
		end 
	end 
	
	def destroy
		@sensor_type = SensorType.find(params[:id])
		@sensor_type.destroy 
		
		respond_to do |format|
			format.html { redirect_to(sensor_types_url) }
		end 
	end 
		
end
