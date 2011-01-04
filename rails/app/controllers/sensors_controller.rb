class SensorsController < ApplicationController

	def new
		@sensor = Sensor.new
		
		respond_to do |format|
			format.html 
			format.xml { render :xml => @sensor }			
	end
	
end
