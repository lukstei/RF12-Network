class ApplicationController < ActionController::Base
	protect_from_forgery
	
	def sensor_type_is_analog?
		return true if @sensor_typ.is_analog
	end 
	
	helper_method :sensor_type_is_analog?
	
end
