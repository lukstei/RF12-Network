class ApplicationController < ActionController::Base

	protect_from_forgery
 	
	def datatype?(object)
		if object.class.to_s == "Float"
			return "Float"
		elsif object.class.to_s == "Fixnum"
			return "Fixnum"
		end 
	end  
  
end
