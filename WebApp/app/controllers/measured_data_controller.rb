class MeasuredDataController < ApplicationController

	before_filter :load_sensor, :except => :destroy 
	
	def create
		@measured_data = @sensor.measured_datas.new(params[:measured_data])
		if @measured_data.save
			respond_to do |format| 
				format.html { redirect_to @sensor, :notice => "Messpunkt hinzugefügt" }
			end 
		else
			respond_to do |format|
				format.html { redirect_to @sensor, :alert => "Hinzufügen des Messpunkts fehlgeschlagen" }
			end 
		end 
	end 
	
	def destroy 
		@sensor = sensors.find(params[:sensor_id])
		@measured_data = @sensor.measured_datas.find(params[:id])
		@measured_data.destroy
		respond_to do |format|
			format.html {redirect_to @sensor, :notice => "Messpunkt gelöscht"}
		end 
	end
	
	private
		def load_sensor
			@sensor = Sensor.find(params[:sensor_id])
		end
	
end
