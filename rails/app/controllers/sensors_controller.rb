class SensorsController < ApplicationController

	def new
		@sensor = Sensor.new
		
		respond_to do |format|
			format.html 
			format.xml { render :xml => @sensor }			
	end
	
	def show
		@sensor = Sensor.find(params[:id])
		
		respond_to do |format|
			format.html #show.html.erb
			format.xml { render :xml => @sensor }
		end 
	end 
	
	def edit
		@sensor = Sensor.find(params[:id])
	end
	
	
	
end
